#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPoint>
#include <QSize>

#include "../Epsilon5-Proto/Epsilon5.pb.h"

enum EMapStatus {
    MS_NoMap,
    MS_Loading,
    MS_Ready
};

enum ETeam {
    T_One,
    T_Second,
    T_Neutral
};

struct TRespPoint {
    int X, Y;
    int SpawnRadius, CaptureRadius;
    bool IsMain;
    bool IsCapturable;
    size_t CpatureTime;
    ETeam Team;
};

class TMaps : public QObject
{
    Q_OBJECT
public:
    explicit TMaps(QObject *parent = 0);
    void LoadMaplist(const QString& fileName);
    void LoadNextMap();
    inline EMapStatus GetStatus() {
        return MapStatus;
    }
    QString GetCurrentMap();
    QSize GetMapSize();
    void SerialiseRespPoints(Epsilon5::World& world, qreal scaleDown);

    inline QVector<TRespPoint>& GetRespPoints() {
        return RespPoints;
    }
signals:
    void SpawnObject(size_t id, int x, int y, double angle);
    void SpawnBorders(const QSize& MapSize);
    void ClearObjects();
    void ClearBorders();
private:
    void LoadConfig(const QString& fileName);
    void LoadObjects(const QString& fileName);
    void LoadRespPoints(const QString& fileName);
private:
    QStringList MapFiles;
    int CurrentMap;
    QSize MapSize;
    EMapStatus MapStatus;
    QVector<TRespPoint> RespPoints;
};
