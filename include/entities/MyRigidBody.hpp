#pragma once

#include <Ogre.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <OgreBulletDynamicsWorld.h>

class MyRigidBody : public OgreBulletDynamics::RigidBody
{
public:
    MyRigidBody(const Ogre::String &name,
                OgreBulletDynamics::DynamicsWorld *world,
                const short collisionGroup = 0,
                const short collisionMask = 0);
                
    virtual ~MyRigidBody();

    void showDebugShape (bool val);
};
