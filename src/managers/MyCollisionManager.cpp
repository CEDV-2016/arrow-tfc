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
                    EnemyManager* enemyManager = EnemyManager::getSingletonPtr();
                    enemyManager->detectCollision(node1->getName());
                  }else if ((node2->getName().substr(0,5).compare("Enemy") == 0) && (node1->getName().substr(0,4).compare("Ball") == 0)) {
                    Node * child  = 0;
                    try {
                        child = _sceneMgr->getRootSceneNode()->getChild(node1->getName());
                    }
                    catch (Ogre::Exception e) {
                        std::cout << node1->getName() << std::endl;
                        continue;
                    }
                    if(child) {
                        _sceneMgr->getRootSceneNode()->removeChild(child);
                        std::cout << node1->getName() << std::endl;
                     }

                    EnemyManager* enemyManager = EnemyManager::getSingletonPtr();
                    enemyManager->detectCollision(node2->getName());
                  }
                }
              }
            }
        }
    }
}

MyCollisionManager& MyCollisionManager::getSingleton() {
  assert(msSingleton);
  return (*msSingleton);
}

MyCollisionManager* MyCollisionManager::getSingletonPtr() {
  assert(msSingleton);
  return msSingleton;
}
