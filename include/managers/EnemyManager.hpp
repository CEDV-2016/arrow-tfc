#pragma once

#include <Ogre.h>
#include <string>
#include "Enemy.hpp"

using namespace std;

class EnemyManager : public Ogre::Singleton<EnemyManager>
{
public:
  EnemyManager();
  ~EnemyManager();

  static EnemyManager& getSingleton ();
  static EnemyManager* getSingletonPtr ();

  void createEnemy(int phase);
  void update( Ogre::Real deltaT );
  void detectCollision(std::string nameObA, std::string nameObB);

private:
  std::map<std::string, Enemy*> _enemies;

  void createPhaseOne();
};
