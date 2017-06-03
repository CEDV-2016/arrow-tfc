#include "EnemyManager.hpp"

template<> EnemyManager* Ogre::Singleton<EnemyManager>::msSingleton = 0;

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
  //delete _enemies;
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
  for (int i = 0; i < 3; i++) {
    std::string enemyId = "Enemy" + std::to_string(i);
    Enemy* enemy = new Enemy("Arrow", enemyId, Ogre::Vector3 ( i, 0, i ));
    _enemies.insert(pair<std::string, Enemy*>(enemyId, enemy));
  }
}

void EnemyManager::update( Ogre::Real deltaT )
{

}

void EnemyManager::detectCollision(std::string nameObA, std::string nameObB)
{
  //std::cout << nameObA << " - " << nameObB << std::endl;
  std::map<std::string, Enemy*>::iterator itA;
  std::map<std::string, Enemy*>::iterator itB;

  itA = _enemies.find(nameObA);
  if (itA != _enemies.end()) {
    std::cout << "DentroA" << std::endl;
    //Enemy enemy = itA->second;
    //enemy.reduceLife();
  }

  itB = _enemies.find(nameObB);
  if (itB != _enemies.end()) {
    Enemy* enemy = itB->second;
    std::cout << "DentroB - "<< enemy << std::endl;
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
