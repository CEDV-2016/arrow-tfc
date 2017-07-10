#include "ForgottenForestMap.hpp"
#include "CameraManager.hpp"
#include "PlayState.hpp"

#include <iostream>

ForgottenForestMap::ForgottenForestMap(Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world) :
_sceneMgr( sceneMgr ),
_world( world )
{
}

ForgottenForestMap::~ForgottenForestMap()
{
  destroy();
}

void ForgottenForestMap::create()
{
  // Creating light
  Ogre::Light *light = _sceneMgr->createLight();
  light->setType( Ogre::Light::LT_DIRECTIONAL );
  light->setDirection( Ogre::Vector3(-1, -1, -1) );

  Ogre::SceneNode* light_node = _sceneMgr->createSceneNode("FF_Light");
  light_node->attachObject(light);
  _sceneMgr->getRootSceneNode()->addChild(light_node);

  // Loading the scenario
  std::string map_file = "FF_Ground.mesh";
  Ogre::Entity * forgottenForest_entity  = _sceneMgr->createEntity( map_file );
  Ogre::SceneNode * forgottenForest_node = _sceneMgr->createSceneNode( "FF_Ground" );
  forgottenForest_node->attachObject( forgottenForest_entity );
  _sceneMgr->getRootSceneNode()->addChild( forgottenForest_node );

  map_file = "FF_Rocks.mesh";
  forgottenForest_entity  = _sceneMgr->createEntity( map_file );
  forgottenForest_node = _sceneMgr->createSceneNode( "FF_Rocks" );
  forgottenForest_node->attachObject( forgottenForest_entity );
  _sceneMgr->getRootSceneNode()->addChild( forgottenForest_node );

  map_file = "FF_Trees1.mesh";
  forgottenForest_entity  = _sceneMgr->createEntity( map_file );
  forgottenForest_node = _sceneMgr->createSceneNode( "FF_Trees1" );
  forgottenForest_node->attachObject( forgottenForest_entity );
  _sceneMgr->getRootSceneNode()->addChild( forgottenForest_node );

  map_file = "FF_Trees2.mesh";
  forgottenForest_entity  = _sceneMgr->createEntity( map_file );
  forgottenForest_node = _sceneMgr->createSceneNode( "FF_Trees2" );
  forgottenForest_node->attachObject( forgottenForest_entity );
  _sceneMgr->getRootSceneNode()->addChild( forgottenForest_node );

  // Characters
  std::string characters_file = "FF_Character.mesh";
  Ogre::Entity * characters_entity  = _sceneMgr->createEntity( characters_file );
  Ogre::SceneNode * characters_node = _sceneMgr->createSceneNode( "FF_Characters" );
  characters_node->attachObject( characters_entity );
  _sceneMgr->getRootSceneNode()->addChild( characters_node );

  CameraManager::getSingletonPtr()->setPosition(10, 0, 0);


  TrackManager::getSingletonPtr()->load("Forgotten_Forest.ogg")->play();
}

void ForgottenForestMap::destroy()
{
  try
  {
    _sceneMgr->destroySceneNode( "FF_Light" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "FF_Ground" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "FF_Rocks" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "FF_Trees1" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "FF_Trees2" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "FF_Characters" );
  }
  catch (Ogre::Exception ex) {}
}

enumerations::Maps ForgottenForestMap::checkBoundaries(Ogre::Vector3 player)
{
  if (player.x < -29 && player.z > -11.7)
  {
    std::cout << "COMPLETED!\n";
    PlayState::getSingletonPtr()->getGame()->complete_Forgotten_Forest();
    return enumerations::Maps::CITADEL;
  }

  if (player.x > 47)
  {
    return enumerations::Maps::CITADEL;
  }
  else
  {
    return enumerations::Maps::NONE;
  }
}
