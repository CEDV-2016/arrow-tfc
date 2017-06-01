#pragma once

#include <Ogre.h>
#include "GameObject.hpp"

class GameObjectManager : public Ogre::Singleton<GameObjectManager>
{
public:
    GameObjectManager();
    ~GameObjectManager();

    static GameObjectManager &getSingleton ();
    static GameObjectManager *getSingletonPtr ();

    void update (float delta);
    void addGameObject (std::shared_ptr<GameObject> gameObject);
    void removeAllObjects ();
    void removeActualPhase();
    void hideHUD ();
    void showHUD ();
    int getNumGameObject() { return _gameObjects.size(); };

private:
    std::vector<std::shared_ptr<GameObject>> _gameObjects;

};
