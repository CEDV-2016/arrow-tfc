#include "ParticlesManager.hpp"

template <> ParticlesManager* Ogre::Singleton<ParticlesManager>::msSingleton = 0;

ParticlesManager::ParticlesManager () : _numParticles(0)
{
}

ParticlesManager::~ParticlesManager ()
{
    _particles.clear();
}

ParticlesManager* ParticlesManager::getSingletonPtr ()
{
  assert(msSingleton);
  return msSingleton;
}

ParticlesManager& ParticlesManager::getSingleton ()
{
  assert(msSingleton);
  return *msSingleton;
}

void ParticlesManager::update (float delta)
{
    for (std::map<std::string, Particle*>::iterator it = _particles.begin();
          it != _particles.end();
          ++it)
    {
      Particle* particle = it->second;
      particle->update(delta);
      if (particle->isFinished()) {
        _particles.erase(it->first);
      }
    }
}

void ParticlesManager::createParticle(Ogre::Vector3 position, int type)
{
    std::string name;
    switch (type) {
      case Particle::Type::BULLET_COLLISION:
        name = std::string("Bullet_collision");
        break;
      default:
        break;
    }
    std::cout << "ParticlesMgr - " << name << std::endl;

    Particle* particle = new Particle(name, std::to_string(_numParticles), position);
    _particles.insert(pair<std::string, Particle*>(std::to_string(_numParticles), particle));
    _numParticles++;
}

void ParticlesManager::destroyAllParticles()
{
    _particles.clear();
}
