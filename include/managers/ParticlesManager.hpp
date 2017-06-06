#pragma once

#include "MyParticle.hpp"

using namespace std;

class ParticlesManager : public Ogre::Singleton<ParticlesManager>
{
public:
  ParticlesManager();
  ~ParticlesManager();

  static ParticlesManager& getSingleton ();
  static ParticlesManager* getSingletonPtr ();

  void createParticle (Ogre::Vector3 position, int type);
  void update (float delta);
  void destroyAllParticles ();

private:
  std::map<std::string, MyParticle*> _particles;
  int _numParticles;
};
