#pragma once

#include <Ogre.h>

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"
#include "TrackManager.hpp"
#include "Enumerations.hpp"

class Map
{
public:
  virtual void create() = 0;
  virtual void destroy() = 0;
  virtual enumerations::Maps checkBoundaries(Ogre::Vector3 player) = 0;
};
