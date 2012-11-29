#include "bullet.h"

TBullet::TBullet(double x, double y, double vx, double vy, double d, QObject *parent)
    : TDynamicObject(x, y, vx, vy, 0, parent)
{
    // TODO: Find usage for the unused variable
    Q_UNUSED(d);

    b2CircleShape circle;
    circle.m_p.Set(0, 0);
    circle.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 0.8f;
    fixtureDef.filter.groupIndex = 1;
    Body->CreateFixture(&fixtureDef);

    Ttl = 300;
}

void TBullet::ApplyCustomPhysics() {
    b2Vec2 force(0, 0.1);
    Body->ApplyForceToCenter(force);
    Ttl--;
}
