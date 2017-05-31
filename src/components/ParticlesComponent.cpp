#include "ParticlesComponent.hpp"
#include "ParticlesManager.hpp"

ParticlesComponent::ParticlesComponent (std::shared_ptr<GameObject> gameObject,
  Ogre::Vector3 position, int type, Ogre::Node *node, Ogre::Vector3 relative_position,
  Ogre::Vector3 relative_velocity) : Component(gameObject, Component::Type::PARTICLES),
  _particle(nullptr), _parent(node), _relative_position(relative_position),
  _relative_velocity(relative_velocity)
{
    if (type != VOID) {
        _particle = ParticlesManager::getSingletonPtr()->createParticleSystem(position + relative_position, type);
    }
}

ParticlesComponent::~ParticlesComponent ()
{
    if (_particle) {
        _particle->finish();
        _particle = nullptr;
    }
}

void ParticlesComponent::update (float delta)
{
    if (_parent) {
        if (_particle) {
            Ogre::Vector3 position = _parent->_getDerivedPosition();
            Ogre::Quaternion orientation = _parent->_getDerivedOrientation();
            Ogre::Vector3 relative_position = orientation * _relative_position;
            _particle->setPosition(position + relative_position);
            if (_relative_velocity != Ogre::Vector3::ZERO) {
                Ogre::Vector3 final_direction = orientation * _relative_velocity;
                _particle->setDirection(final_direction);
            }
        }
    }
}

void ParticlesComponent::switchToParticle (int type)
{
    if (_particle) {
        _particle->finish();
        _particle = nullptr;
    }
    if (_parent) {
        Ogre::Vector3 position = _parent->_getDerivedPosition();
        Ogre::Quaternion orientation = _parent->_getDerivedOrientation();
        Ogre::Vector3 relative_position = orientation * _relative_position;
        _particle = ParticlesManager::getSingletonPtr()->createParticleSystem(position + relative_position, type);
    }
}

Ogre::Vector3 ParticlesComponent::getPosition ()
{
    if (_parent) {
        if (_particle) {
            return _parent->_getDerivedPosition() + (_parent->_getDerivedOrientation() * _relative_position);
        }
    }
    return Ogre::Vector3::ZERO;
}


Ogre::Vector3 ParticlesComponent::getDirection ()
{
    if (_parent) {
        if (_particle) {
            return _parent->_getDerivedOrientation() * _relative_velocity;
        }
    }
    return Ogre::Vector3::ZERO;
}

float ParticlesComponent::getMinVelocity ()
{
    if (_particle) {
        return _particle->getMinVelocity();
    }
    return 0;
}

bool ParticlesComponent::isFinished ()
{
    return _particle->isFinished();
}
