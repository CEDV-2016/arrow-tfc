#include "CitadelMap.hpp"

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

  // Characters
  std::string characters_file = "Characters.mesh";
  Ogre::Entity * characters_entity  = _sceneMgr->createEntity( characters_file );
  Ogre::SceneNode * characters_node = _sceneMgr->createSceneNode( "Citadel_Characters" );
  characters_node->attachObject( characters_entity );
  _sceneMgr->getRootSceneNode()->addChild( characters_node );


}

void CitadelMap::destroy()
{
  _sceneMgr->destroySceneNode( _sceneMgr->getSceneNode( "Citadel" ) );
  _sceneMgr->destroySceneNode( _sceneMgr->getSceneNode( "Citadel_Light" ) );
  _sceneMgr->destroySceneNode( _sceneMgr->getSceneNode( "Citadel_Characters" ) );
}
