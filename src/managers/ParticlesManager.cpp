#include "ParticlesManager.hpp"

template <> ParticlesManager* Ogre::Singleton<ParticlesManager>::msSingleton = nullptr;

ParticlesManager::ParticlesManager () : _numParticles(0)
{
}

ParticlesManager::~ParticlesManager ()
{
    _particles.clear();
}

ParticlesManager* ParticlesManager::getSingletonPtr ()
{
    return msSingleton;
}

ParticlesManager& ParticlesManager::getSingleton ()
{
    assert(msSingleton);
    return *msSingleton;
}

void ParticlesManager::update (float delta)
{
    int size = _particles.size();
    for (int i = 0; i < size; ++i) {
        _particles[i]->update(delta);
        if (_particles[i]->isFinished()) {
            _particles.erase(_particles.begin() + i);
            --i; --size;
        }
    }
}

std::shared_ptr<Particle> ParticlesManager::createParticle(Ogre::Vector3 position, int type)
{
    std::string name;
    switch (type) {
        default:
            break;
    }
    std::shared_ptr<Particle> particle = std::make_shared<Particle>("Bullet_collision", "0", Ogre::Vector3 ( 0, 0, 0 ));
    _particles.push_back(particle);
    return particle;
}

void ParticlesManager::destroyAllParticles()
{
    _particles.clear();
}
