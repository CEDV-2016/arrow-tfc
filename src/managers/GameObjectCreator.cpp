#include "GameObjectCreator.hpp"
#include "PlayerBullet.hpp"
#include "NodeComponent.hpp"
#include "PhysicsComponent.hpp"
#include "StatusComponent.hpp"
#include "RigidBodyAnimationComponent.hpp"
#include "ParticlesComponent.hpp"

template<> GameObjectCreator* Ogre::Singleton<GameObjectCreator>::msSingleton = nullptr;

GameObjectCreator::GameObjectCreator () :
    _gameObjectMgr(nullptr), _cameraMgr(nullptr), _enemy(0),_sceneMgr(nullptr)
{
    _gameObjectMgr = GameObjectManager::getSingletonPtr();
}

GameObjectCreator::~GameObjectCreator ()
{
}

GameObjectCreator* GameObjectCreator::getSingletonPtr ()
{
    return msSingleton;
}

GameObjectCreator& GameObjectCreator::getSingleton ()
{
    assert(msSingleton);
    return *msSingleton;
}

void GameObjectCreator::createPlayerBullet(Ogre::Vector3 position, Ogre::Vector3 direction)
{
    std::shared_ptr<PlayerBullet> bullet = std::make_shared<PlayerBullet>();
    bullet->initComponents(position, direction);
    _gameObjectMgr->addGameObject(bullet);
}

void GameObjectCreator::createEnemy(Ogre::Vector3 position)
{
    std::shared_ptr<GameObject> enemy = std::make_shared<GameObject>();
    std::shared_ptr<NodeComponent> nodeCmp = std::make_shared<NodeComponent>(enemy, "Enemy", _enemy);
    std::shared_ptr<PhysicsComponent> physicsCmp =
        std::make_shared<PhysicsComponent>(enemy, nodeCmp->getNode(), nodeCmp->getEntity(),
        std::string("Enemy") + std::to_string(_enemy), PhysicsComponent::Type::ENEMY,
        PhysicsComponent::Shape::CONVEX, true, position, Ogre::Vector3::ZERO);
    std::shared_ptr<RigidBodyAnimationComponent> rigidAnimationCmp =
        std::make_shared<RigidBodyAnimationComponent>(enemy, physicsCmp, nodeCmp->getEntity());
    std::shared_ptr<StatusComponent> statusCmp =
        std::make_shared<StatusComponent>(enemy, 6, StatusComponent::Type::ENEMY);
    physicsCmp->setStatusComponent(statusCmp);
    enemy->addComponent(rigidAnimationCmp);
    enemy->addComponent(physicsCmp);
    enemy->addComponent(nodeCmp);
    enemy->addComponent(statusCmp);
    _gameObjectMgr->addGameObject(enemy);
    ++_enemy;
}

const float GameObjectCreator::MAX_WALL_BULLETS = 10;
const float GameObjectCreator::ENEMY_BULLET_VELOCITY = 15;
