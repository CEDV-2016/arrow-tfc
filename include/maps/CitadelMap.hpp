#pragma once

#include <string>

#include "Map.hpp"

class CitadelMap : public Map
{
public:
  CitadelMap( Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world );
  ~CitadelMap();

  void create();
  void destroy();
  enumerations::Maps checkBoundaries(Ogre::Vector3 player);

private:
  Ogre::SceneManager * _sceneMgr;
  OgreBulletDynamics::DynamicsWorld * _world;
};
