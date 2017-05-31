#include "MyRigidBody.hpp"

MyRigidBody::MyRigidBody(const Ogre::String &name,
                         OgreBulletDynamics::DynamicsWorld *world,
                         const short collisionGroup,
                         const short collisionMask)
                         : OgreBulletDynamics::RigidBody(name, world, collisionGroup, collisionMask)
{
}

MyRigidBody::~MyRigidBody ()
{
}

void MyRigidBody::showDebugShape (bool val)
{
    RigidBody::showDebugShape(val);
    if (mShapeNode) {
        mDebugNode->setVisible(false);
    }
}
