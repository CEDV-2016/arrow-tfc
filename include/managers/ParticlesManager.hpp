#pragma once

#include "Particle.hpp"
#include <memory>

class ParticlesManager : public Ogre::Singleton<ParticlesManager>
{
public:
    ParticlesManager();
    ~ParticlesManager();

    void update (float delta);
    std::shared_ptr<Particle> createParticle (Ogre::Vector3 position, int type);
    void destroyAllParticles ();
    int getNumberOfParticles() { return _particles.size(); };

    static ParticlesManager& getSingleton ();
    static ParticlesManager* getSingletonPtr ();

protected:
    std::vector<std::shared_ptr<Particle>> _particles;
    int _numParticles;
};
