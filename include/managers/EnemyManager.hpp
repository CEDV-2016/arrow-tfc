#pragma once

#include <Ogre.h>
#include <string>

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
  void detectCollision(std::string name);

private:
  std::vector<Ogre::SceneNode> _enemies;
};
