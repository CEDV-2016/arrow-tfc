#pragma once

#include <Ogre.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"

class Enemy
{
public:
  Enemy(std::string mesh_name, std::string id, Ogre::Vector3 position);
  ~Enemy();

  void update(Ogre::Real deltaT);
  void reduceLife();
  bool shoot();
  void destroy();

  Ogre::Vector3 getPosition();
  Ogre::SceneNode * getSceneNode();

private:
  Ogre::SceneNode *_node;
  Ogre::Entity *_entity;
  Ogre::SceneManager *_sceneMgr;
  Ogre::Vector3 _position;
  int _life;
};
