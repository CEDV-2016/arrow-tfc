#include "Enemy.hpp"
#include "SoundFXManager.hpp"
#include "MyPhysicsManager.hpp"
#include "MyParticle.hpp"
#include "ParticlesManager.hpp"

Enemy::Enemy(std::string mesh_name, std::string id, Ogre::Vector3 position)
{
  _sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("SceneManager");
  _entity  = _sceneMgr->createEntity( id + std::string("Entity"),
      mesh_name + std::string(".mesh") );
  _node = _sceneMgr->createSceneNode( id);
  _node->attachObject( _entity );
  _sceneMgr->getRootSceneNode()->addChild( _node );
  _position = position;
  _life = 3;
  _id = id;

  OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter =
      new OgreBulletCollisions::StaticMeshToShapeConverter( _entity );
  OgreBulletCollisions::TriangleMeshCollisionShape *enemy_trimesh =
      trimeshConverter->createTrimesh();
  OgreBulletDynamics::RigidBody *enemy_physic =
      new OgreBulletDynamics::RigidBody( mesh_name + id,
      MyPhysicsManager::getSingletonPtr()->getPhysicWorld());
  enemy_physic->setShape( _node, enemy_trimesh, 0.8, 0.95,
      0, _position, Ogre::Quaternion::IDENTITY );
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
  if (_life == 0) {
    _sceneMgr->getRootSceneNode()->removeChild(_node);
    ParticlesManager* particlesMgr = ParticlesManager::getSingletonPtr();
    particlesMgr->createParticle(_position, MyParticle::Type::BULLET_COLLISION);
  }
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
