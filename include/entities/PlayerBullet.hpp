#pragma once

#include <Ogre.h>
#include "GameObject.hpp"

class PlayerBullet : public GameObject
{
public:
    PlayerBullet() : GameObject() {};
    ~PlayerBullet() {};

    void initComponents(Ogre::Vector3 position, Ogre::Vector3 direction);

private:
    static int _id;
    const float PLAYER_BULLET_VELOCITY = 70;
};
