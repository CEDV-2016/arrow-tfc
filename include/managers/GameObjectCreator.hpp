#pragma once

#include "GameObjectManager.hpp"
#include "CameraManager.hpp"
#include "Player.hpp"

class GameObjectCreator : public Ogre::Singleton<GameObjectCreator>
{
public:
    GameObjectCreator();
    ~GameObjectCreator();

    static GameObjectCreator &getSingleton ();
    static GameObjectCreator *getSingletonPtr ();

    void createPlayerBullet(Ogre::Vector3 position, Ogre::Vector3 direction);
    void createEnemy(Ogre::Vector3 position);
    void resetCounters () { _enemy = 0; };

    static const float MAX_WALL_BULLETS;
    static const float ENEMY_BULLET_VELOCITY;
    static const int NUMBER_ENEMY_PARTS = 3;
    static const int NUMBER_PLAYER_PARTS = 3;

protected:
    GameObjectManager *_gameObjectMgr;
    CameraManager *_cameraMgr;
    unsigned int _enemy;
    Ogre::SceneManager *_sceneMgr;
};
