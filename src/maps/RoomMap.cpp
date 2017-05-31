#include "RoomMap.hpp"

#include <iostream>

RoomMap::RoomMap(Ogre::SceneManager * sceneMgr, OgreBulletDynamics::DynamicsWorld * world) :
_sceneMgr( sceneMgr ),
_world( world )
{
}

RoomMap::~RoomMap() {}

void RoomMap::create()
{
  std::string map_file = "Scenario.mesh";

  // Creating light
  Ogre::Light *light = _sceneMgr->createLight();
  light->setType( Ogre::Light::LT_DIRECTIONAL );
  light->setDirection( Ogre::Vector3(-1, -1, -1) );

  Ogre::SceneNode* light_node = _sceneMgr->createSceneNode("RoomLight");
  light_node->attachObject(light);
  _sceneMgr->getRootSceneNode()->addChild(light_node);

  // Creating the scenario
  // Ogre::StaticGeometry* stage = _sceneMgr->createStaticGeometry("Stage");
  // Ogre::Entity* ent_stage = _sceneMgr->createEntity( map_file );
  // stage->addEntity( ent_stage, Ogre::Vector3(0, 0, 0) );
  // stage->build();

  Ogre::Entity * room_entity  = _sceneMgr->createEntity( map_file );
  Ogre::SceneNode * room_node = _sceneMgr->createSceneNode( "Room" );
  room_node->attachObject( room_entity );
  _sceneMgr->getRootSceneNode()->addChild( room_node );

  // Creating the physic room
  OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = new OgreBulletCollisions::StaticMeshToShapeConverter( room_entity );

  OgreBulletCollisions::TriangleMeshCollisionShape *room_trimesh = trimeshConverter->createTrimesh();

  OgreBulletDynamics::RigidBody *physic_room = new OgreBulletDynamics::RigidBody( "Room", _world );
  // Restitucion, friccion y masa
  physic_room->setShape( room_node, room_trimesh, 0.8, 0.95, 0, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);

  loadDartboards();

  // Bola de prueba
  Ogre::Entity *entity = _sceneMgr->createEntity("balldeprueba", "ball.mesh");
  Ogre::SceneNode *node = _sceneMgr->getRootSceneNode()->createChildSceneNode();
  node->attachObject(entity);
  node->scale( Ogre::Vector3(0.45, 0.45, 0.45) );

  OgreBulletCollisions::SphereCollisionShape *ballShape = new OgreBulletCollisions::SphereCollisionShape( 0.5 );
  OgreBulletDynamics::RigidBody *rigidBall = new OgreBulletDynamics::RigidBody("balldeprueba", _world);

  Ogre::Vector3 position = Ogre::Vector3(-8.5, 10, -8.7);
  rigidBall->setShape(node, ballShape, 0.05, 0.05, 0.3, position, Ogre::Quaternion::IDENTITY);
}

void RoomMap::destroy()
{
  _sceneMgr->destroySceneNode( _sceneMgr->getSceneNode( "Room" ) );
  _sceneMgr->destroySceneNode( _sceneMgr->getSceneNode( "RoomLight" ) );

  std::stringstream dartboard_name;
  dartboard_name.str("");
  for (int i=1; i<=5; i++)
  {
    dartboard_name << "Dartboard" << i;

    // http://www.ogre3d.org/forums/viewtopic.php?f=2&t=15994
    try
    {
      _sceneMgr->destroySceneNode( dartboard_name.str() );
    }
    catch (Ogre::Exception ex)
    {
      // The scenenode doesn't exist
    }
    dartboard_name.str("");
  }
}


void RoomMap::loadDartboards()
{
  std::stringstream filename;
  filename.str("");

  for (int i=1; i<=5; i++)
  {
    filename << "Dartboard" << i << ".mesh";
    loadSingleDartboard( filename.str() );
    filename.str("");
  }
}

Ogre::SceneNode * RoomMap::loadSingleDartboard( std::string dartboard_file )
{

  Ogre::Entity * dartboard_entity;
  Ogre::SceneNode * dartboard_node;

  std::stringstream dartboard_name;
  dartboard_name << "Dartboard" << _dartboard_counter;
  _dartboard_counter++;

  dartboard_entity  = _sceneMgr->createEntity( dartboard_name.str(), dartboard_file );
  dartboard_node = _sceneMgr->createSceneNode( dartboard_name.str() );
  dartboard_node->attachObject( dartboard_entity );
  _sceneMgr->getRootSceneNode()->addChild( dartboard_node );

  OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = new OgreBulletCollisions::StaticMeshToShapeConverter( dartboard_entity );
  OgreBulletCollisions::TriangleMeshCollisionShape *dartboard_trimesh = trimeshConverter->createTrimesh();
  OgreBulletDynamics::RigidBody *physic_dartboard = new OgreBulletDynamics::RigidBody( dartboard_name.str(), _world );
  physic_dartboard->setShape( dartboard_node, dartboard_trimesh, 0.8, 0.95, 0, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY );

  return dartboard_node;
}
