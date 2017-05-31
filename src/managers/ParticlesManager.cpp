#include "ParticlesManager.hpp"
#include "ParticlesComponent.hpp"

template <> ParticlesManager* Ogre::Singleton<ParticlesManager>::msSingleton = nullptr;

ParticlesManager::ParticlesManager () : _id_counter(0)
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

std::shared_ptr<MyParticleSystem> ParticlesManager::createParticleSystem(Ogre::Vector3 position, int type)
{
    std::string name;
    switch (type) {
        default:
            break;
    }
    std::shared_ptr<MyParticleSystem> particle = std::make_shared<MyParticleSystem>(position, name);
    _particles.push_back(particle);
    return particle;
}

void ParticlesManager::destroyAllParticles()
{
    _particles.clear();
}
