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

  _cameraMgr = CameraManager::getSingletonPtr();
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
  _cameraMgr = nullptr;
}

void Enemy::update(Ogre::Real deltaT)
{
  if (playerIsInRange() && playerIsVisible()) {
    if ((getPosition() - _cameraMgr->getPosition()).normalise() < MIN_DISTANCE_TO_PLAYER) {
      attack(deltaT);
    }else{
      chasing(deltaT);
    }
  }else{
    stop();
  }
}

void Enemy::chasing(Ogre::Real deltaT)
{
  Ogre::Vector3 org = getPosition();
  Ogre::Vector3 des = _cameraMgr->getPosition();
  int posX = (des.x - org.x) > 0 ? 1 : -1;
  int posZ = (des.z - org.z) > 0 ? 1 : -1;
  Ogre::Vector3 vec = Ogre::Vector3(posX * 0.45f * deltaT, 0, posZ * 0.45f * deltaT);
  _node->translate(vec, Ogre::SceneNode::TS_LOCAL);

  /*Ogre::Radian rad = org.angleBetween(des);
  Ogre::Vector3 up = _node->getOrientation() * Ogre::Vector3::UNIT_Y;
  Ogre::Quaternion qRotation = Ogre::Quaternion(rad, up);
  _node->rotate(qRotation);*/
}

void Enemy::stop()
{

}

void Enemy::attack(Ogre::Real deltaT)
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
  return _node->convertLocalToWorldPosition(_node->getPosition());
}

Ogre::SceneNode * Enemy::getSceneNode()
{
  return _node;
}

bool Enemy::playerIsInRange()
{
  return (getPosition() - _cameraMgr->getPosition()).normalise() < MAX_DISTANCE_TO_PLAYER;
}

bool Enemy::playerIsVisible()
{
  Ogre::Vector3 vect = getPosition() - _cameraMgr->getPosition();
  Ogre::Vector3 monsterDirection =
      getSceneNode()->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
  return monsterDirection.directionEquals(vect, Ogre::Degree(VISIBLE_ANGLE));
}
