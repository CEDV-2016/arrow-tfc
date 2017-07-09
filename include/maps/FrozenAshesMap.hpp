#pragma once

#include <string>

#include "Map.hpp"

class FrozenAshesMap : public Map
{
public:
  FrozenAshesMap( Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world );
  ~FrozenAshesMap();

  void create();
  void destroy();

private:
  Ogre::SceneManager * _sceneMgr;
  OgreBulletDynamics::DynamicsWorld * _world;
};
