#pragma once

#include "MyParticleSystem.hpp"
#include <memory>

class ParticlesManager : public Ogre::Singleton<ParticlesManager>
{
public:
    ParticlesManager();
    ~ParticlesManager();

    void update (float delta);
    std::shared_ptr<MyParticleSystem> createParticleSystem (Ogre::Vector3 position, int type);
    void destroyAllParticles ();
    int getNumberOfParticles() { return _particles.size(); };

    static ParticlesManager& getSingleton ();
    static ParticlesManager* getSingletonPtr ();

protected:
    std::vector<std::shared_ptr<MyParticleSystem>> _particles;
    int _id_counter;
};
