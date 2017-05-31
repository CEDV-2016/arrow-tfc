#pragma once

#include <Ogre.h>
#include <OgreParticleSystem.h>

class MyParticleSystem
{
public:
    MyParticleSystem(Ogre::Vector3 position, std::string name);
    ~MyParticleSystem();

    void update (float delta);
    void setPosition (Ogre::Vector3 position);
    void finish ();
    bool isFinished () { return _is_finished; };
    void setDirection (Ogre::Vector3 direction);
    float getMinVelocity ();

private:
    Ogre::ParticleSystem *_particle;
    Ogre::SceneNode *_parent;

    bool _is_finished;
    float _time_to_finish;
    static int _id;
};
