#pragma once

#include "Component.hpp"
#include "MyParticleSystem.hpp"

class ParticlesComponent : public Component
{
public:
    ParticlesComponent(std::shared_ptr<GameObject> gameObject, Ogre::Vector3 position,
      int type, Ogre::Node *node = nullptr, Ogre::Vector3 relative_position = Ogre::Vector3::ZERO,
      Ogre::Vector3 relative_velocity = Ogre::Vector3::ZERO);
    virtual ~ParticlesComponent();

    void update (float delta);
    void setParent (Ogre::Node *node) { _parent = node; };
    void switchToParticle (int type);
    Ogre::Vector3 getPosition ();
    Ogre::Vector3 getDirection ();
    float getMinVelocity ();
    bool isFinished () override;

    enum Type {
        VOID
    };
protected:
    std::shared_ptr<MyParticleSystem> _particle;
    Ogre::Node *_parent;
    Ogre::Vector3 _relative_position;
    Ogre::Vector3 _relative_velocity;
};
