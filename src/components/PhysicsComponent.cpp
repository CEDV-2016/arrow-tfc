#include "PhysicsComponent.hpp"
#include "GameObject.hpp"
#include "ParticlesManager.hpp"
#include "ParticlesComponent.hpp"
#include "SoundFXManager.hpp"

PhysicsComponent::PhysicsComponent (std::shared_ptr<GameObject> gameObject,
  Ogre::SceneNode *node, Ogre::Entity *entity, std::string id, int type, int shape,
  bool manually_controlled, Ogre::Vector3 position, Ogre::Vector3 size, Ogre::Quaternion orientation)
  : Component(gameObject, Component::Type::PHYSICS), _body(nullptr), _shape(nullptr),
  _type(type), _statusCmp(nullptr), _affected_by_collisions(true)
{
    short collides_with = 0;
    switch (_type) {
        case Type::PLAYER:
            collides_with = player_collides_with;
            break;
        case Type::ENEMY:
            collides_with = enemy_collides_with;
            break;
        default:
            break;
    }
    MyPhysicsManager* physicsMgr = MyPhysicsManager::getSingletonPtr();
    _body = new MyRigidBody(id, physicsMgr->getPhysicWorld(), _type, collides_with);
    switch (shape) {
        case Shape::CONVEX:
            {
                std::shared_ptr<OgreBulletCollisions::VertexIndexToShape> meshToShapeConverter;
                meshToShapeConverter = std::make_shared<OgreBulletCollisions::AnimatedMeshToShapeConverter>(entity);
                _shape = meshToShapeConverter->createTrimesh();
                _body->setShape(node, _shape, 0.01, 1, 90.0, position, orientation);
                break;
            }
        case Shape::STATIC_CONVEX:
            {
                std::shared_ptr<OgreBulletCollisions::VertexIndexToShape> meshToShapeConverter;
                meshToShapeConverter = std::make_shared<OgreBulletCollisions::StaticMeshToShapeConverter>(entity);
                _shape = meshToShapeConverter->createConvex();
                _body->setShape(node, _shape, 0.01, 1, 90.0, position, orientation);
                break;
            }
        case Shape::CYLINDER:
            break;
        case Shape::BOX:
            break;
        case Shape::SPHERE:
            _shape = new OgreBulletCollisions::SphereCollisionShape(size.x);
            _body->setShape(node, _shape, 0.01, 1, 90.0, position, orientation);
            break;
        case Shape::STATIC_PLANE:
            {
                Ogre::Vector3 facing = Ogre::Vector3::ZERO;
                float position_value = 0;
                if (position.x != 0) {
                    facing = Ogre::Vector3(1, 0, 0);
                    position_value = position.x;
                }
                else if (position.y != 0) {
                    facing = Ogre::Vector3(0, 1, 0);
                    position_value = position.y;
                }
                else if (position.z != 0) {
                    facing = Ogre::Vector3(0, 0, 1);
                    position_value = position.z;
                }
                _shape = new OgreBulletCollisions::StaticPlaneCollisionShape(facing, position_value);
                _body->setStaticShape(_shape, 0.1, 3.0);
                break;
            }
        case Shape::CAPSULE:
            {
                _shape = new OgreBulletCollisions::CapsuleCollisionShape(size.x, size.y, Ogre::Vector3::UNIT_Z);
                _body->setShape(node, _shape, 0.01, 1, 90.0, position, orientation);
                break;
            }
        default:
            break;
    }
    auto btbody = _body->getBulletRigidBody();
    _body->disableDeactivation();
    if (manually_controlled) {
        btbody->setLinearFactor(btVector3(0, 0, 0));
        btbody->setAngularFactor(btVector3(0, 0, 0));
    }
    btbody->setUserPointer(this);
}

btTransform PhysicsComponent::getTransformation ()
{
    return _body->getBulletRigidBody()->getWorldTransform();
}

void PhysicsComponent::setTransformation(btTransform transform)
{
    _body->getBulletRigidBody()->setWorldTransform(transform);
}

void PhysicsComponent::onCollision(PhysicsComponent* cmp)
{
    if (!_affected_by_collisions || !cmp->isAffectedByCollisions()) {
        return;
    }
    if (_type == Type::PLAYER || _type == Type::ENEMY) {
        if (cmp->getType() == Type::PLAYER || cmp->getType() == Type::ENEMY) {
            if (_statusCmp) {
                _statusCmp->reduceLife(1);
            }
            //ParticlesManager::getSingletonPtr()->createParticleSystem(getPosition(), ParticlesComponent::Type::BULLET_COLLISION);
        }
    }
}

void PhysicsComponent::setGravity (Ogre::Vector3 gravity)
{
    _body->getBulletRigidBody()->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}
