#pragma once

#include <string>

#include "Map.hpp"

class ForgottenForestMap : public Map
{
public:
  ForgottenForestMap( Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world );
  ~ForgottenForestMap();

  void create();
  void destroy();

private:
  Ogre::SceneManager * _sceneMgr;
  OgreBulletDynamics::DynamicsWorld * _world;
};
