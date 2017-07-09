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

private:
  Ogre::SceneManager * _sceneMgr;
  OgreBulletDynamics::DynamicsWorld * _world;
};
