#pragma once

#include <vector>

#include <Ogre.h>
#include <OgreSingleton.h>

#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsStaticPlaneShape.h>
#include <Shapes/OgreBulletCollisionsBoxShape.h>

#include "Map.hpp"
#include "Fader.hpp"
#include "CitadelMap.hpp"
#include "ForgottenForestMap.hpp"
#include "FrozenAshesMap.hpp"
#include "Enumerations.hpp"
#include "MyPhysicsManager.hpp"

class MapManager : public Ogre::Singleton<MapManager>
{
public:
  typedef std::shared_ptr<Map> MapPtr;

  MapManager( Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * _pyhsicWorld );
  ~MapManager();

  void changeMap(enumerations::Maps id, bool fade);
  void loadMap();
  void fadeOut( std::function<void ()> callback = nullptr );
  void fadeIn ( std::function<void ()> callback = nullptr );
  void destroyAllMaps();
  void update( Ogre::Real deltaT );

  enumerations::Maps checkCurrentMapBoundaries(Ogre::Vector3 player);

  OgreBulletDynamics::DynamicsWorld * getPhysicWorld();

  // Inherited from Ogre::Singleton.
  static MapManager& getSingleton ();
  static MapManager* getSingletonPtr ();

private:
  std::map<enumerations::Maps, MapPtr> _maps;

  enumerations::Maps _currentMap, _nextMap;
  Fader * _fader;
  Ogre::SceneManager * _sceneMgr;

  OgreBulletDynamics::DynamicsWorld * _pyhsicWorld;

  bool changing_map = false;
  
  void initMaps();
};
