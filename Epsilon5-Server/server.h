#pragma once

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QHash>
#include "../Epsilon5-Proto/defines.h"
#include "maps.h"

class TApplication;
class TClient;

class TServer : public QObject
{
    Q_OBJECT
public:
    TServer(QObject *parent = 0);
    void Start();
    void Send(const QHostAddress &ip, quint16 port, const QByteArray &data, EPacketType packetType);
    TApplication* Application();
    void RespawnDeadClients();
signals:
    void NewPlayer(size_t id, ETeam);
    void PlayerDisconnected(size_t id);
private slots:
    void DataReceived();
private:
    void timerEvent(QTimerEvent *);
    void SendWorld();
    void DisconnectInactive();
private:
    QHash<QString, size_t> Ids;
    QHash<size_t, TClient*> Clients;
    QHash<QHostAddress, size_t> Ips;
    QUdpSocket* Server;
    size_t CurrentId;
};
