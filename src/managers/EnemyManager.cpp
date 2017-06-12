#include "EnemyManager.hpp"

template<> EnemyManager* Ogre::Singleton<EnemyManager>::msSingleton = 0;

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
  _enemies.clear();
}

void EnemyManager::createEnemy(int phase)
{
  switch (phase) {
    case 1:
      createPhaseOne();
      break;
    default:
      break;
  }
}

void EnemyManager::createPhaseOne(){
  for (int i = 0; i < 1; i++) {
    std::string enemyId = "Enemy" + std::to_string(i);
    Enemy* enemy = new Enemy("Arrow", enemyId, Ogre::Vector3 ( i, 0, i*2 ));
    _enemies.insert(pair<std::string, Enemy*>(enemyId, enemy));
  }
}

void EnemyManager::update( Ogre::Real deltaT )
{
  for (std::map<std::string, Enemy*>::iterator it = _enemies.begin();
        it != _enemies.end();
        ++it)
  {
    Enemy* enemy = it->second;
    enemy->update(deltaT);
  }
}

void EnemyManager::detectCollision(std::string nameOb)
{
    std::map<std::string, Enemy*>::iterator itB;
    itB = _enemies.find(nameOb);
    if (itB != _enemies.end()) {
      Enemy* enemy = itB->second;
      enemy->reduceLife();
    }
}

EnemyManager& EnemyManager::getSingleton() {
  assert(msSingleton);
  return (*msSingleton);
}

EnemyManager* EnemyManager::getSingletonPtr() {
  assert(msSingleton);
  return msSingleton;
}
