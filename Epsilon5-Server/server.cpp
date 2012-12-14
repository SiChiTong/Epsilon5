#include <QtEndian>
#include "../utils/uexception.h"
#include "application.h"
#include "client.h"
#include "server.h"
#include "player.h"

TServer::TServer(QObject *parent)
    : QObject(parent)
    , Server(new QUdpSocket(this))
    , CurrentId(1)
{
    connect(Server, SIGNAL(readyRead()), SLOT(DataReceived()));
}

void TServer::Start() {
    if (Server->bind(QHostAddress(
        Application()->GetSettings()->GetServerAddress()),
        Application()->GetSettings()->GetServerPort()))
    {
        this->startTimer(20); // TODO: Remove MN
    } else {
        throw UException(QString("Can't listen to port %1")
            .arg(Application()->GetSettings()->GetServerPort()));
    }
}

void TServer::DataReceived() {
    const quint32 MAX_PACKET_DATA_SIZE = 16000;
    QHostAddress sender;
    quint16 senderPort;
    QByteArray data;
    data.resize(MAX_PACKET_DATA_SIZE);

    qint32 size = Server->readDatagram(data.data(), data.size(), &sender, &senderPort);
    if (size==-1) {
        return;
    }
    data.remove(size, data.size());

    QString addr = sender.toString() + ":" + QString::number(senderPort);
    size_t id;
    if (Ids.find(addr) != Ids.end()) {
        id = Ids[addr];
    } else {
        CurrentId ++;
        if (CurrentId > 100000) {
            CurrentId = 0;
        }
        Ids.insert(addr, CurrentId);
        id = CurrentId;
    }

    auto clientIt = Clients.find(id);
    if (clientIt == Clients.end())
    {       // New client connected
        auto ipIt = Ips.find(sender);
        if (ipIt == Ips.end()) {
            ipIt = Ips.insert(sender, 0);
        }

        if (ipIt.value() >= 2) {
            return;
        }
        ipIt.value()++;

        TClient* client = new TClient(sender, senderPort, id, this);
        connect(client, SIGNAL(SpawnPlayer(size_t, ETeam)), this, SIGNAL(NewPlayer(size_t, ETeam)));
        connect(client, SIGNAL(PlayerConnected()), Application()->GetWorld(), SLOT(NeedFullPacket()));
        connect(this, SIGNAL(PlayerKilled(size_t)), client, SLOT(Killed(size_t)));
        clientIt = Clients.insert(id, client);
    }

    clientIt.value()->OnDataReceived(data);
}

void TServer::timerEvent(QTimerEvent*) {
    DisconnectInactive();
    RespawnDeadClients();
    SendWorld();
}

void TServer::DisconnectInactive() {
    auto i = Clients.begin();
    for (; i != Clients.end();)
    {
        i.value()->EnlargeSeen();
        if (i.value()->GetLastSeen() > 200)
        {
            qDebug() << "Player " << i.value()->GetNick()
                     << "(" << i.value()->GetAddr().toString() << ") disconnected";
            auto ipIt = Ips.find(i.value()->GetAddr());
            if (ipIt != Ips.end() && ipIt.value()>0)
                ipIt.value()--;
            emit PlayerDisconnected(i.value()->GetId());
            i.value()->deleteLater();
            i = Clients.erase(i);
        } else {
            i++;
        }
    }
}

void TServer::SendWorld()
{
    QByteArray data=Application()->GetWorld()->Serialize();
    for (auto i = Clients.begin(); i != Clients.end(); i++) {
        i.value()->SendWorld(data);
    }
}

TApplication* TServer::Application() {
    return (TApplication*)(parent());
}

// Send packet to the client in form:
// [PACKET_TYPE] [ORIGIN_DATA_SIZE] [PACKED_DATA_SIZE] [PACKED_DATA]
void TServer::Send(const QHostAddress &ip, quint16 port,
    const QByteArray &originData, EPacketType packetType)
{
    QByteArray sendPacket;
    QByteArray packedData = qCompress(originData, 5);
    quint16 originDataSize = qToBigEndian<quint16>(originData.size());
    quint16 packedDataSize = qToBigEndian<quint16>(packedData.size());
    sendPacket += QChar(packetType);
    sendPacket += QByteArray((const char*) &originDataSize, sizeof(quint16));
    sendPacket += QByteArray((const char*) &packedDataSize, sizeof(quint16));
    sendPacket += packedData;
    Server->writeDatagram(sendPacket, ip, port);
}

void TServer::RespawnDeadClients() {
    for (auto i = Clients.begin(); i != Clients.end(); i++) {
        i.value()->ReSpawn();
    }
}

void TServer::SerialiseStats(Epsilon5::World& world) {
    for (auto i = Clients.begin(); i != Clients.end(); i++) {
        auto stat = world.add_players_stat();
        stat->set_score((*i)->GetScore());
        stat->set_kills((*i)->GetKills());
        stat->set_deaths((*i)->GetDeaths());
        stat->set_id((*i)->GetId());
    }

}
