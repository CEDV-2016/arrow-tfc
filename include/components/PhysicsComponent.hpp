#pragma once

#include <Ogre.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsCapsuleShape.h>
#include <Shapes/OgreBulletCollisionsConvexHullShape.h>
#include <Shapes/OgreBulletCollisionsTrimeshShape.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>
#include <Utils/OgreBulletCollisionsMeshToShapeConverter.h>
#include "Component.hpp"
#include "StatusComponent.hpp"
#include "MyRigidBody.hpp"
#include "MyPhysicsManager.hpp"

class PhysicsComponent : public Component
{
public:
    PhysicsComponent(std::shared_ptr<GameObject> gameObject, Ogre::SceneNode *node,
      Ogre::Entity *entity, std::string id, int type, int shape, bool manually_controlled,
      Ogre::Vector3 position = Ogre::Vector3::ZERO, Ogre::Vector3 size = Ogre::Vector3::ZERO,
      Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY);
    virtual ~PhysicsComponent() {
        if (_body) {
            delete _body;
        }
        if (_shape) {
            delete _shape;
        }
        _statusCmp = nullptr;
    };

    void setTransformation(btTransform transform);
    Ogre::Vector3 getPosition () { if (_body) { return _body->getCenterOfMassPosition(); } return Ogre::Vector3::ZERO; }
    Ogre::Quaternion getOrientation () { if (_body) { return _body->getWorldOrientation(); } return Ogre::Quaternion::ZERO; }
    btTransform getTransformation();
    int getType () { return _type; };
    void setLinearVelocity (Ogre::Vector3 velocity) { if (_body) { _body->setLinearVelocity(velocity); } };
    void setAngularVelocity (Ogre::Vector3 velocity) { if (_body) { _body->setAngularVelocity(velocity); } };
    void onCollision (PhysicsComponent *cmp);
    void setStatusComponent (std::shared_ptr<StatusComponent> statusCmp) { _statusCmp = statusCmp; };
    void showDebugShape(bool val) {
        _body->showDebugShape(val);
    }
    void setGravity (Ogre::Vector3 gravity);

    enum Type {
        PLAYER = 1,
        ENEMY = 2,
    };

    enum Shape {
        CONVEX,
        STATIC_CONVEX,
        CYLINDER,
        BOX,
        SPHERE,
        STATIC_PLANE,
        CAPSULE
    };

    void setAffectedByCollisions(bool affected) { _affected_by_collisions = affected; };
    bool isAffectedByCollisions() { return _affected_by_collisions; };

    static const short player_collides_with = ENEMY;
    static const short enemy_collides_with = PLAYER;

protected:
    MyRigidBody *_body;
    OgreBulletCollisions::CollisionShape *_shape;
    int _type;
    std::shared_ptr<StatusComponent> _statusCmp;
    bool _affected_by_collisions;
};
