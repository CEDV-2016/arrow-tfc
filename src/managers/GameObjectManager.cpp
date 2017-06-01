#include "GameObjectManager.hpp"
#include "Player.hpp"
#include "StatusComponent.hpp"
//#include "GameObjectCreator.h"

template<> GameObjectManager* Ogre::Singleton<GameObjectManager>::msSingleton = nullptr;

GameObjectManager::GameObjectManager ()
{
}

GameObjectManager::~GameObjectManager ()
{
    _gameObjects.clear();
}

GameObjectManager* GameObjectManager::getSingletonPtr ()
{
    return msSingleton;
}

GameObjectManager& GameObjectManager::getSingleton ()
{
    assert(msSingleton);
    return *msSingleton;
}

void GameObjectManager::update (float delta)
{
    int size = _gameObjects.size();
    for (int i = 0; i < size; ++i) {
        _gameObjects[i]->update(delta);
        if (_gameObjects[i]->isFinished()) {
            _gameObjects[i]->removeComponents();
            _gameObjects.erase(_gameObjects.begin() + i);
            --i; --size;
        }
    }
}

void GameObjectManager::addGameObject (std::shared_ptr<GameObject> gameObject)
{
    _gameObjects.push_back(gameObject);
}

void GameObjectManager::removeAllObjects ()
{
    int size = _gameObjects.size();
    for (int i = 0; i < size; ++i) {
        _gameObjects[i]->removeComponents();
    }
    _gameObjects.clear();
}

void GameObjectManager::removeActualPhase ()
{
    //(GameObjectCreator::getSingletonPtr()->getActualPhase())->removeComponents();
}

void GameObjectManager::hideHUD () {
    /*int size = _gameObjects.size();
    for (int i = 0; i < size; ++i) {
        std::shared_ptr<Component> cmp = _gameObjects[i]->getComponent(Component::CEGUI);
        if (cmp != nullptr) {
            std::shared_ptr<CEGUIComponent> ceguiCmp = std::static_pointer_cast<CEGUIComponent>(cmp);
            ceguiCmp->visibilityHUD(false);
        }
        cmp = _gameObjects[i]->getComponent(Component::INPUT);
        if (cmp != nullptr) {
            std::shared_ptr<InputComponent> ceguiCmp = std::static_pointer_cast<InputComponent>(cmp);
            ceguiCmp->visibilityEyehole(false);
        }
    }*/
}

void GameObjectManager::showHUD () {
    /*int size = _gameObjects.size();
    for (int i = 0; i < size; ++i) {
        std::shared_ptr<Component> cmp = _gameObjects[i]->getComponent(Component::CEGUI);
        if (cmp != nullptr) {
            std::shared_ptr<CEGUIComponent> ceguiCmp = std::static_pointer_cast<CEGUIComponent>(cmp);
            ceguiCmp->visibilityHUD(true);
        }
        cmp = _gameObjects[i]->getComponent(Component::INPUT);
        if (cmp != nullptr) {
            std::shared_ptr<InputComponent> ceguiCmp = std::static_pointer_cast<InputComponent>(cmp);
            ceguiCmp->visibilityEyehole(true);
        }
    }*/
}
