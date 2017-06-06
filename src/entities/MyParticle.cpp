#include "MyParticle.hpp"
#include <limits>

MyParticle::MyParticle (std::string name, std::string id, Ogre::Vector3 position)
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

MyParticle::~MyParticle ()
{
    _particle->detachFromParent();
    _sceneMgr->destroyParticleSystem(_particle);
    _sceneMgr->getRootSceneNode()->removeChild(_node);
    _sceneMgr->destroySceneNode(_node);
}

void MyParticle::update (Ogre::Real deltaT)
{
    _particle->_update(deltaT);
    _timeToFinish -= deltaT;
    if (_timeToFinish < 0) {
        _isFinished = true;
    }
}

void MyParticle::finish ()
{
  _particle->getEmitter(0)->setEmissionRate(0);
  _timeToFinish = _particle->getEmitter(0)->getMaxTimeToLive();
}

void MyParticle::changePosition (Ogre::Vector3 position)
{
  _node->setPosition(position);
}

void MyParticle::changeDirection (Ogre::Vector3 direction)
{
  _particle->getEmitter(0)->setDirection(direction);
}

float MyParticle::getMinVelocity ()
{
  return _particle->getEmitter(0)->getMinParticleVelocity();
}
