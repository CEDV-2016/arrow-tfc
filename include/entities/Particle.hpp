#pragma once

#include <Ogre.h>
#include <OgreParticleSystem.h>

class Particle
{
public:
    Particle(std::string name, std::string id, Ogre::Vector3 position);
    ~Particle();

    void update (Ogre::Real deltaT);
    void changePosition (Ogre::Vector3 position);
    void finish ();
    bool isFinished () { return _isFinished; };
    void changeDirection (Ogre::Vector3 direction);
    float getMinVelocity ();

    enum Type {
      BULLET_COLLISION
    };

private:
    Ogre::ParticleSystem *_particle;
    Ogre::SceneNode *_node;
    Ogre::SceneManager *_sceneMgr;
    bool _isFinished;
    Ogre::Real _timeToFinish;
    std::string _id;
};
