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
  std::cout << "Update " << _id << " - "<< playerIsVisible() << std::endl;
  if (playerIsInRange()) {
    //_node->translate(_cameraMgr->getPosition(), Ogre::SceneNode::TS_LOCAL);
    Ogre::Vector3 cameraVec = _cameraMgr->getPosition();
    Ogre::Radian angulo = _position.angleBetween(cameraVec);
    std::cout << "Angle: " << angulo << std::endl;


  }
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
  return (getPosition() - _cameraMgr->getPosition()).normalise() < MIN_DISTANCE_TO_PLAYER;
}

bool Enemy::playerIsVisible()
{
  Ogre::Vector3 vect = getPosition() - _cameraMgr->getPosition();
  Ogre::Vector3 monsterDirection =
      getSceneNode()->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
  return monsterDirection.directionEquals(vect, Ogre::Degree(VISIBLE_ANGLE));
}
