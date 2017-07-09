#include "ForgottenForestMap.hpp"

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

  Ogre::SceneNode* light_node = _sceneMgr->createSceneNode("ForgottenForest_Light");
  light_node->attachObject(light);
  _sceneMgr->getRootSceneNode()->addChild(light_node);

  // Loading the scenario
  std::string map_file = "FF_Ground.mesh";
  Ogre::Entity * forgottenForest_entity  = _sceneMgr->createEntity( map_file );
  Ogre::SceneNode * forgottenForest_node = _sceneMgr->createSceneNode();
  forgottenForest_node->attachObject( forgottenForest_entity );
  _sceneMgr->getRootSceneNode()->addChild( forgottenForest_node );

  map_file = "FF_Rocks.mesh";
  forgottenForest_entity  = _sceneMgr->createEntity( map_file );
  forgottenForest_node = _sceneMgr->createSceneNode();
  forgottenForest_node->attachObject( forgottenForest_entity );
  _sceneMgr->getRootSceneNode()->addChild( forgottenForest_node );

  map_file = "FF_Trees1.mesh";
  forgottenForest_entity  = _sceneMgr->createEntity( map_file );
  forgottenForest_node = _sceneMgr->createSceneNode();
  forgottenForest_node->attachObject( forgottenForest_entity );
  _sceneMgr->getRootSceneNode()->addChild( forgottenForest_node );

  map_file = "FF_Trees2.mesh";
  forgottenForest_entity  = _sceneMgr->createEntity( map_file );
  forgottenForest_node = _sceneMgr->createSceneNode();
  forgottenForest_node->attachObject( forgottenForest_entity );
  _sceneMgr->getRootSceneNode()->addChild( forgottenForest_node );

  // Characters
  std::string characters_file = "FF_Character.mesh";
  Ogre::Entity * characters_entity  = _sceneMgr->createEntity( characters_file );
  Ogre::SceneNode * characters_node = _sceneMgr->createSceneNode( "ForgottenForest_Characters" );
  characters_node->attachObject( characters_entity );
  _sceneMgr->getRootSceneNode()->addChild( characters_node );

  TrackManager::getSingletonPtr()->load("Forgotten_Forest.ogg")->play();
}

void ForgottenForestMap::destroy()
{
  // _sceneMgr->destroySceneNode( _sceneMgr->getSceneNode( "ForgottenForest" ) );
  // _sceneMgr->destroySceneNode( _sceneMgr->getSceneNode( "ForgottenForest_Light" ) );
  // _sceneMgr->destroySceneNode( _sceneMgr->getSceneNode( "ForgottenForest_Characters" ) );
}
