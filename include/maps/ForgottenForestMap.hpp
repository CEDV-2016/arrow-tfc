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
  enumerations::Maps checkBoundaries(Ogre::Vector3 player);

private:
  Ogre::SceneManager * _sceneMgr;
  OgreBulletDynamics::DynamicsWorld * _world;
};
