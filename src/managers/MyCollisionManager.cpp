#include "MyCollisionManager.hpp"
#include "MyPhysicsManager.hpp"
#include "PlayState.hpp"
#include "EnemyManager.hpp"

#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"

template<> MyCollisionManager* Ogre::Singleton<MyCollisionManager>::msSingleton = 0;

MyCollisionManager::MyCollisionManager(Ogre::SceneManager * sceneMgr)
{
  _sceneMgr = sceneMgr;
  _world = MyPhysicsManager::getSingletonPtr()->getPhysicWorld();
}

MyCollisionManager::~MyCollisionManager()
{
}

void MyCollisionManager::update( Ogre::Real deltaT ){
  detectCollision();
}

void MyCollisionManager::detectCollision()
{
  /*btCollisionWorld *bulletWorld = _world->getBulletCollisionWorld();
  int numManifolds = bulletWorld->getDispatcher()->getNumManifolds();

  for (int i=0; i<numManifolds; i++) {
    btPersistentManifold* contactManifold =
      bulletWorld->getDispatcher()->getManifoldByIndexInternal(i);
    btCollisionObject* obA =
      (btCollisionObject*)(contactManifold->getBody0());
    btCollisionObject* obB =
      (btCollisionObject*)(contactManifold->getBody1());

    OgreBulletCollisions::Object *obOB_A1 = _world->findObject(obA);
    OgreBulletCollisions::Object *obOB_B1 = _world->findObject(obB);
    if (obOB_A1 && obOB_B1) {
      Ogre::SceneNode* node1 = obOB_A1->getRootNode();
      Ogre::SceneNode* node2 = obOB_B1->getRootNode();
      if (node1 > 0 && node2 > 0) {
        EnemyManager* enemyManager = EnemyManager::getSingletonPtr();
        enemyManager->detectCollision(node1->getName(), node2->getName());
      }
    }
  }*/



    btCollisionWorld *collisionWorld = _world->getBulletCollisionWorld();
    int numManifolds = collisionWorld->getDispatcher()->getNumManifolds();

    for (int i=0;i<numManifolds;i++)
    {
        btPersistentManifold* contactManifold =  collisionWorld->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* obA = (btCollisionObject *) contactManifold->getBody0();
        btCollisionObject* obB = (btCollisionObject *) contactManifold->getBody1();

        int numContacts = contactManifold->getNumContacts();
        for (int j=0;j<numContacts;j++)
        {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            if (pt.getDistance()<0.f)
            {
              OgreBulletCollisions::Object *obOB_A1 = _world->findObject(obA);
              OgreBulletCollisions::Object *obOB_B1 = _world->findObject(obB);
              if (obOB_A1 && obOB_B1) {
                Ogre::SceneNode* node1 = obOB_A1->getRootNode();
                Ogre::SceneNode* node2 = obOB_B1->getRootNode();
                if (node1 > 0 && node2 > 0) {
                  if ((node1->getName().substr(0,5).compare("Enemy") == 0) && (node2->getName().substr(0,4).compare("Ball") == 0)) {
                    //_sceneMgr->getRootSceneNode()->removeAndDestroyChild (node2->getName());
                    EnemyManager* enemyManager = EnemyManager::getSingletonPtr();
                    enemyManager->detectCollision(node1->getName());
                  }else if ((node2->getName().substr(0,5).compare("Enemy") == 0) && (node1->getName().substr(0,4).compare("Ball") == 0)) {
                    //_sceneMgr->getRootSceneNode()->removeAndDestroyChild (node1->getName());
                    EnemyManager* enemyManager = EnemyManager::getSingletonPtr();
                    enemyManager->detectCollision(node2->getName());
                  }
                }
              }
            }
        }
    }

    /*std::stringstream dartboard_id;
    for(int j=0; j<3; j++){
        dartboard_id.str("");
        dartboard_id << "Enemy" << j;
        Ogre::SceneNode* drain = _sceneMgr->getSceneNode(dartboard_id.str());

        OgreBulletCollisions::Object *obDrain = _world->findObject(drain);
        OgreBulletCollisions::Object *obOB_A = _world->findObject(obA);
        OgreBulletCollisions::Object *obOB_B = _world->findObject(obB);

        if ((obOB_A == obDrain) || (obOB_B == obDrain)) {
          Ogre::SceneNode* node = NULL;
          if ((obOB_A == obDrain) && (obOB_A)) {
    	       node = obOB_A->getRootNode();
             delete obOB_A;
          }
          else if ((obOB_B == obDrain) && (obOB_B)) {
    	       node = obOB_B->getRootNode();
             delete obOB_B;
          }
          if (node) {
    	       std::cout << node->getName() << std::endl;
    	       //_sceneMgr->getRootSceneNode()->removeAndDestroyChild (node->getName());



             //PlayState* playState = PlayState::getSingletonPtr();
             //playState-> updateDartboards();
          }
        }
    }*/
  //}
}

MyCollisionManager& MyCollisionManager::getSingleton() {
  assert(msSingleton);
  return (*msSingleton);
}

MyCollisionManager* MyCollisionManager::getSingletonPtr() {
  assert(msSingleton);
  return msSingleton;
}
