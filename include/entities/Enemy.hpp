#pragma once

#include <Ogre.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"
#include "CameraManager.hpp"

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

  enum State {
    STOP,
    WALKING,
    CHASING,
    ATTACKING
  };

private:
  const float MIN_DISTANCE_TO_PLAYER = 5.0f;
  const float MAX_DISTANCE_TO_PLAYER = 7.0f;
  const float TIME_BETWEEN_ATTACKS = 1.0f;
  const float VISIBLE_ANGLE = 45.0f;

  Ogre::SceneNode *_node;
  Ogre::Entity *_entity;
  Ogre::SceneManager *_sceneMgr;
  Ogre::Vector3 _position;
  int _life;
  std::string _id;
  CameraManager* _cameraMgr;

  bool playerIsInRange();
  bool playerIsVisible();
};
