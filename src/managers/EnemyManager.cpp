#include "EnemyManager.hpp"
#include "Enemy.hpp"

template<> EnemyManager* Ogre::Singleton<EnemyManager>::msSingleton = 0;

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::createEnemy(int phase)
{
  new Enemy("Arrow", 1);
}

void EnemyManager::update( Ogre::Real deltaT )
{

}

void EnemyManager::detectCollision(std::string name)
{

}

EnemyManager& EnemyManager::getSingleton() {
  assert(msSingleton);
  return (*msSingleton);
}

EnemyManager* EnemyManager::getSingletonPtr() {
  assert(msSingleton);
  return msSingleton;
}
