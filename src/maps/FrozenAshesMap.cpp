#include "FrozenAshesMap.hpp"
#include "CameraManager.hpp"

#include <iostream>

FrozenAshesMap::FrozenAshesMap(Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world) :
  _sceneMgr( sceneMgr ),
  _world( world )
{
}

FrozenAshesMap::~FrozenAshesMap()
{
  destroy();
}

void FrozenAshesMap::create()
{
  // Creating light
  Ogre::Light *light = _sceneMgr->createLight();
  light->setType( Ogre::Light::LT_DIRECTIONAL );
  light->setDirection( Ogre::Vector3(-1, -1, -1) );

  Ogre::SceneNode* light_node = _sceneMgr->createSceneNode("FA_Light");
  light_node->attachObject(light);
  _sceneMgr->getRootSceneNode()->addChild(light_node);

  // Loading the scenario
  std::string map_file = "FA_Ground.mesh";
  Ogre::Entity * aux_entity  = _sceneMgr->createEntity( map_file );
  Ogre::SceneNode * aux_node = _sceneMgr->createSceneNode( "FA_Ground");
  aux_node->attachObject( aux_entity );
  _sceneMgr->getRootSceneNode()->addChild( aux_node );

  map_file = "FA_Fence.mesh";
  aux_entity  = _sceneMgr->createEntity( map_file );
  aux_node = _sceneMgr->createSceneNode( "FA_Fence" );
  aux_node->attachObject( aux_entity );
  _sceneMgr->getRootSceneNode()->addChild( aux_node );

  map_file = "FA_Trees.mesh";
  aux_entity  = _sceneMgr->createEntity( map_file );
  aux_node = _sceneMgr->createSceneNode( "FA_Trees" );
  aux_node->attachObject( aux_entity );
  _sceneMgr->getRootSceneNode()->addChild( aux_node );

  map_file = "FA_Character.mesh";
  aux_entity  = _sceneMgr->createEntity( map_file );
  aux_node = _sceneMgr->createSceneNode( "FA_Character" );
  aux_node->attachObject( aux_entity );
  _sceneMgr->getRootSceneNode()->addChild( aux_node );

  CameraManager::getSingletonPtr()->setPosition(-9.5, 0, -6.65);

  TrackManager::getSingletonPtr()->load("Frozen_Ashes.ogg")->play();
}

void FrozenAshesMap::destroy()
{
  try
  {
    _sceneMgr->destroySceneNode( "FA_Light" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "FA_Ground" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "FA_Fence" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "FA_Trees" );
  }
  catch (Ogre::Exception ex) {}

  try
  {
    _sceneMgr->destroySceneNode( "FA_Character" );
  }
  catch (Ogre::Exception ex) {}
}
