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

  void loadDartboards();
  Ogre::SceneNode * loadSingleDartboard( std::string dartboard_file );

private:
  std::string map_file = "Citaed.mesh";

  Ogre::SceneManager * _sceneMgr;
  OgreBulletDynamics::DynamicsWorld * _world;

  int _dartboard_counter = 0;
};
