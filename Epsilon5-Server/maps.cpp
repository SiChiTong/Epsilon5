#include <QFile>
#include <QTextStream>
#include "../utils/uexception.h"
#include "../utils/usettings.h"
#include "../utils/ucast.h"
#include "maps.h"

#include <QDebug>

TMaps::TMaps(QObject *parent)
    : QObject(parent)
    , MapStatus(MS_NoMap)
{
}

void TMaps::LoadMaplist(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UException("Error opening file " + fileName);
    }
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        MapFiles.push_back(line);
    }
    CurrentMap = -1;
    MapStatus = MS_NoMap;
}

void TMaps::LoadNextMap() {
    MapStatus = MS_Loading;
    if (MapFiles.size() == 0) {
        throw UException("No maps found");
    }
    CurrentMap ++;
    if (CurrentMap >= MapFiles.size()) {
        CurrentMap = 0;
    }
    emit ClearObjects();
    emit ClearBorders();
    LoadConfig("maps/" + MapFiles[CurrentMap] + "/config.ini");
    LoadObjects("maps/" + MapFiles[CurrentMap] + "/objects.txt");
    LoadRespPoints("maps/" + MapFiles[CurrentMap] + "/points.txt");
    emit SpawnBorders(GetMapSize());
    MapStatus = MS_Ready;
}

void TMaps::LoadConfig(const QString& fileName) {
    USettings conf;
    conf.Load(fileName);
    bool ok = true;
    MapSize.setWidth(conf.GetParameter("width"));
    if (!ok) {
        throw UException("Error parsing " + fileName);
    }
    MapSize.setHeight(conf.GetParameter("height"));
    if (!ok) {
        throw UException("Error parsing " + fileName);
    }
}

void TMaps::LoadObjects(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UException("Error opening " + fileName);
    }
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        QStringList objectParams = line.split(":");
        if (objectParams.size() != 4) {
            throw UException("Error parsing " + fileName);
        }

        int id = FromString(objectParams[3]);
        int x = FromString(objectParams[0]);
        int y = FromString(objectParams[1]);
        double angle = FromString(objectParams[2]);

        emit SpawnObject(id, x, y, angle);
    }
}


void TMaps::LoadRespPoints(const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UException("Error opening " + fileName);
    }
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        QStringList params = line.split(":");
        if (params.size() != 8) {
            throw UException("Error parsing " + fileName);
        }

        TRespPoint point;

        //x:y:capture_radius:spawn_radius:is_capturable:is_main:capture_time:team
        point.X = FromString(params[0]);
        point.Y = FromString(params[1]);
        point.CaptureRadius = FromString(params[2]);
        point.IsCapturable = FromString(params[2]);
        point.IsMain = FromString(params[3]);
        point.CpatureTime = FromString(params[4]);
        point.Team = FromString(params[5]) ? T_One : T_Second;
        RespPoints.push_back(point);
    }
}

QString TMaps::GetCurrentMap() {
    if (CurrentMap == -1 || MapFiles.size() < CurrentMap) {
        throw UException("Map not initialised");
    }
    return MapFiles[CurrentMap];
}

QSize TMaps::GetMapSize() {
    if (CurrentMap == -1 || MapFiles.size() < CurrentMap) {
        throw UException("Map not initialised");
    }
    return MapSize;
}

void TMaps::SerialiseRespPoints(Epsilon5::World& world, qreal scaleDown) {
    for (auto i = RespPoints.begin(); i != RespPoints.end(); i++) {
        auto point = world.add_resp_poits();
        point->set_x(scaleDown * i->X);
        point->set_y(scaleDown * i->Y);
        point->set_is_main(i->IsMain);
        point->set_team(i->Team);
    }
}
