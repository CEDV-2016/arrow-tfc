#include "Enemy.hpp"
#include "SoundFXManager.hpp"
#include "MyPhysicsManager.hpp"

Enemy::Enemy(std::string mesh_name, int id)
{
  _sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("SceneManager");
  _entity  = _sceneMgr->createEntity( mesh_name + std::string("Entity") + std::to_string(id),
      mesh_name + std::string(".mesh") );
  _node = _sceneMgr->createSceneNode( mesh_name + std::to_string(id) );
  _node->attachObject( _entity );
  _sceneMgr->getRootSceneNode()->addChild( _node );
  _position = Ogre::Vector3 ( 0, 0.5, -20 );
  _life = 3;

  OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter =
      new OgreBulletCollisions::StaticMeshToShapeConverter( _entity );
  OgreBulletCollisions::TriangleMeshCollisionShape *enemy_trimesh =
      trimeshConverter->createTrimesh();
  OgreBulletDynamics::RigidBody *enemy_physic =
      new OgreBulletDynamics::RigidBody( mesh_name + std::to_string(id),
      MyPhysicsManager::getSingletonPtr()->getPhysicWorld());
  enemy_physic->setShape( _node, enemy_trimesh, 0.8, 0.95,
      0, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY );
}

Enemy::~Enemy()
{
  if (_node) {
      _node->getParent()->removeChild(_node);
      _node->detachAllObjects();
      _sceneMgr->destroySceneNode(_node);
      _node = nullptr;
  }
  if (_entity) {
      _sceneMgr->destroyEntity(_entity);
      _entity = nullptr;
  }
  _sceneMgr = nullptr;
}

void Enemy::update(Ogre::Real deltaT)
{

}

void Enemy::reduceLife()
{
  _life--;
}

bool Enemy::shoot()
{
  return true;
}

void Enemy::destroy()
{
  //SoundFXManager::getSingletonPtr()->load("explosion.wav")->play();
  //_sceneMgr->destroySceneNode( _node );
}

Ogre::Vector3 Enemy::getPosition()
{
  return _position;
}

Ogre::SceneNode * Enemy::getSceneNode()
{
  return _node;
}
