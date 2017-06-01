#include "StatusComponent.hpp"
#include "GameObject.hpp"
//#include "RankingManager.h"
//#include "NodeComponent.h"
//#include "GameObjectCreator.h"
//#include "ParticlesManager.h"
#include "ParticlesComponent.hpp"
#include "PhysicsComponent.hpp"
//#include "EnemyLoader.h"

StatusComponent::StatusComponent(std::shared_ptr<GameObject> gameObject, int life, int type) :
Component(gameObject, Component::Type::STATUS), _life(life), _type(type), _max_life(life),
_time_alive(0), _time_invulnerable_remaining(0), _score_added(false)
{
    if (_type == Type::ENEMY ) {
        ++_num_active_enemies;
    }
}

StatusComponent::~StatusComponent()
{
    if (_type == Type::ENEMY ) {
        --_num_active_enemies;
        //if(_num_active_enemies==0)
            //EnemyLoader::getSingletonPtr()->checkEnemiesState();
    }
}

void StatusComponent::update(float delta) {
    _time_invulnerable_remaining -= delta;
    _time_alive += delta;
    if (!isAlive()) {
        /*if (!_score_added) {
            RankingManager::getSingletonPtr()->addScore(_type);
            _score_added = true;
            Ogre::Vector3 position = std::static_pointer_cast<PhysicsComponent>(_gameObject->getComponent(Component::Type::PHYSICS))->getPosition();
            position.z += 2;
            ParticlesManager::getSingletonPtr()->createParticleSystem(position, ParticlesComponent::Type::ENEMY_DEATH);
        }
        if (_type == Type::ENEMY1 || _type == Type::ENEMY2 || _type == Type::ENEMY3 || _type == Type::ENEMY4 || _type == Type::PLAYER1 || _type == Type::PLAYER2) {
            switch(_type) {
                case Type::ENEMY1:
                    GameObjectCreator::getSingletonPtr()->createPartsEnemy(std::static_pointer_cast<NodeComponent>(_gameObject->getComponent(Component::Type::NODE))->getPosition(), 1);
                    break;
                case Type::ENEMY2:
                    GameObjectCreator::getSingletonPtr()->createPartsEnemy(std::static_pointer_cast<NodeComponent>(_gameObject->getComponent(Component::Type::NODE))->getPosition(), 2);
                    break;
                case Type::ENEMY3:
                    GameObjectCreator::getSingletonPtr()->createPartsEnemy(std::static_pointer_cast<NodeComponent>(_gameObject->getComponent(Component::Type::NODE))->getPosition(), 3);
                    break;
                case Type::ENEMY4:
                    GameObjectCreator::getSingletonPtr()->createPartsEnemy(std::static_pointer_cast<NodeComponent>(_gameObject->getComponent(Component::Type::NODE))->getPosition(), 4);
                    break;
                case Type::PLAYER1:
                    GameObjectCreator::getSingletonPtr()->createPartsPlayer(std::static_pointer_cast<NodeComponent>(_gameObject->getComponent(Component::Type::NODE))->getPosition(), 1);
                    break;
                case Type::PLAYER2:
                    GameObjectCreator::getSingletonPtr()->createPartsPlayer(std::static_pointer_cast<NodeComponent>(_gameObject->getComponent(Component::Type::NODE))->getPosition(), 2);
                    break;
                default:
                    break;
            }
        }*/
        _gameObject->finish();
    }
}

void StatusComponent::reduceLife (int l) {
    if (_time_invulnerable_remaining < 0) {
        _life -= l;
        if (_type == Type::ENEMY ) {
                //std::static_pointer_cast<NodeComponent>(_gameObject->getComponent(Component::Type::NODE))->changeToDamagedMaterial();
        }
    }
}

void StatusComponent::addLife (int l) {
    _life += l;
    if (_life > _max_life) {
        _life = _max_life;
    }
}

int StatusComponent::_num_active_enemies = 0;
