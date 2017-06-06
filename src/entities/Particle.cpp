#include "Particle.hpp"
#include <limits>

Particle::Particle (std::string name, std::string id, Ogre::Vector3 position)
: _particle(nullptr), _node(nullptr), _isFinished(false)
{
    _sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("SceneManager");
    _particle = _sceneMgr->createParticleSystem("ParticleSystem" + id, name);
    _node = _sceneMgr->createSceneNode(id);
    _node->attachObject(_particle);
    _node->setPosition(position);
    _sceneMgr->getRootSceneNode()->addChild(_node);
    _id = id;

    if (_particle->getEmitter(0)->getMaxDuration() > 0) {
        _timeToFinish = _particle->getEmitter(0)->
            getMaxDuration() + _particle->getEmitter(0)->getMaxTimeToLive();
    }
    else {
        _timeToFinish = std::numeric_limits<float>::max();
    }
}

Particle::~Particle ()
{
    _particle->detachFromParent();
    _sceneMgr->destroyParticleSystem(_particle);
    _sceneMgr->getRootSceneNode()->removeChild(_node);
    _sceneMgr->destroySceneNode(_node);
}

void Particle::update (Ogre::Real deltaT)
{
    _particle->_update(deltaT);
    _timeToFinish -= deltaT;
    if (_timeToFinish < 0) {
        _isFinished = true;
    }
}

void Particle::finish ()
{
  _particle->getEmitter(0)->setEmissionRate(0);
  _timeToFinish = _particle->getEmitter(0)->getMaxTimeToLive();
}

void Particle::changePosition (Ogre::Vector3 position)
{
  _node->setPosition(position);
}

void Particle::changeDirection (Ogre::Vector3 direction)
{
  _particle->getEmitter(0)->setDirection(direction);
}

float Particle::getMinVelocity ()
{
  return _particle->getEmitter(0)->getMinParticleVelocity();
}
