/**
* @file
* Definition of Player
*/
#include "../Eps5World/player.h"

Player::Player(QObject *parent) :
    QObject(parent)
{
    _id=0;
    _x=0;
    _y=0;
    _vx=0;
    _vy=0;
    _angle=0;
}

void Player::applyPhysics()
{
    _x+=0.01;
    _y+=0.01;
    // TODO: Make physics
}
