#include "MyParticleSystem.hpp"
#include <limits>

MyParticleSystem::MyParticleSystem (Ogre::Vector3 position, std::string name) :
 _particle(nullptr), _parent(nullptr), _is_finished(false)
 {
    Ogre::SceneManager* sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("SceneManager");
    _parent = sceneMgr->createSceneNode("ParticleNode" + std::to_string(_id));
    _parent->setPosition(position);
    sceneMgr->getRootSceneNode()->addChild(_parent);
    _particle = sceneMgr->createParticleSystem("ParticleSystem" + std::to_string(_id), name);
    _parent->attachObject(_particle);
    ++_id;
    if (_particle->getEmitter(0)->getMaxDuration() > 0) {
        _time_to_finish = _particle->getEmitter(0)->getMaxDuration() + _particle->getEmitter(0)->getMaxTimeToLive();
    }
    else {
        _time_to_finish = std::numeric_limits<float>::max();
    }
}

MyParticleSystem::~MyParticleSystem ()
{
    _particle->detachFromParent();
    Ogre::SceneManager *sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("SceneManager");
    sceneMgr->destroyParticleSystem(_particle);
    sceneMgr->getRootSceneNode()->removeChild(_parent);
    sceneMgr->destroySceneNode(_parent);
}

void MyParticleSystem::update (float delta)
{
    _particle->_update(delta);
    _time_to_finish -= delta;
    if (_time_to_finish < 0) {
        _is_finished = true;
    }
}

void MyParticleSystem::setPosition (Ogre::Vector3 position)
{
    _parent->setPosition(position);
}

void MyParticleSystem::finish ()
{
    _particle->getEmitter(0)->setEmissionRate(0);
    _time_to_finish = _particle->getEmitter(0)->getMaxTimeToLive();
}

void MyParticleSystem::setDirection (Ogre::Vector3 direction)
{
    _particle->getEmitter(0)->setDirection(direction);
}

float MyParticleSystem::getMinVelocity ()
{
    return _particle->getEmitter(0)->getMinParticleVelocity();
}

int MyParticleSystem::_id = 0;
