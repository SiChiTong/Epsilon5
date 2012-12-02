#pragma once

#include <QTime>
#include "../Epsilon5-Proto/Epsilon5.pb.h"
#include "dynamicobject.h"
#include "maps.h"

class TBullet;

class TPlayer : public TDynamicObject
{
    Q_OBJECT
public:
    TPlayer(size_t id, TMaps* maps, QObject *parent = 0);
    inline size_t GetId() { return Id; }
    inline size_t GetHP() { return HP; }
    void Hit();
    void ApplyCustomPhysics();
    void SetNickname(const QString& nickName);
    inline QString GetNickname() {
        return NickName;
    }

signals:
    void SpawnBullet(TBullet*);
    void Death(size_t id);
public slots:
    void ApplyControl(const Epsilon5::Control &control);
private:
    b2Vec2 Force;
    size_t Id;
    QTime lastShoot;
    QString NickName;
    TMaps* Maps;
    size_t HP;
    TObjectInfo CollisionInfo;
};
