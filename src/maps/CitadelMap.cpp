#include "CitadelMap.hpp"
#include "CameraManager.hpp"

#include <iostream>

CitadelMap::CitadelMap(Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world) :
_sceneMgr( sceneMgr ),
_world( world )
{
}

CitadelMap::~CitadelMap()
{
  destroy();
}

void CitadelMap::create()
{
  // Creating light
  Ogre::Light *light = _sceneMgr->createLight();
  light->setType( Ogre::Light::LT_DIRECTIONAL );
  light->setDirection( Ogre::Vector3(1, -1, 1) );

  Ogre::SceneNode* light_node = _sceneMgr->createSceneNode("Citadel_Light");
  light_node->attachObject(light);
  _sceneMgr->getRootSceneNode()->addChild(light_node);

  // Creating the scenario
  std::string map_file = "Citadel.mesh";
  Ogre::Entity * citadel_entity  = _sceneMgr->createEntity( map_file );
  Ogre::SceneNode * citadel_node = _sceneMgr->createSceneNode( "Citadel" );
  citadel_node->attachObject( citadel_entity );
  _sceneMgr->getRootSceneNode()->addChild( citadel_node );

  map_file = "Cliff.mesh";
  citadel_entity  = _sceneMgr->createEntity( map_file );
  citadel_node = _sceneMgr->createSceneNode( "Citadel_Cliff" );
  citadel_node->attachObject( citadel_entity );
  _sceneMgr->getRootSceneNode()->addChild( citadel_node );

  // Characters
  std::string characters_file = "Characters.mesh";
  Ogre::Entity * characters_entity  = _sceneMgr->createEntity( characters_file );
  Ogre::SceneNode * characters_node = _sceneMgr->createSceneNode( "Citadel_Characters" );
  characters_node->attachObject( characters_entity );
  _sceneMgr->getRootSceneNode()->addChild( characters_node );

  CameraManager::getSingletonPtr()->setPosition(1, 0, -5);

  TrackManager::getSingletonPtr()->load("Citadel.ogg")->play();

}

void CitadelMap::destroy()
{
  try
  {
    _sceneMgr->destroySceneNode( "Citadel_Light" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "Citadel" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "Citadel_Cliff" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "Citadel_Characters" );
  }
  catch (Ogre::Exception ex) {}
}

enumerations::Maps CitadelMap::checkBoundaries(Ogre::Vector3 player)
{
  if (player.x > 23)
  {
    return enumerations::Maps::FORGOTTEN_FOREST;
  }
  if (player.x < -22.2)
  {
    return enumerations::Maps::FROZEN_ASHES;
  }
  else
  {
    return enumerations::Maps::NONE;
  }
}
