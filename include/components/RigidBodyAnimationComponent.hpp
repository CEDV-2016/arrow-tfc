#pragma once

#include "Component.hpp"
#include "PhysicsComponent.hpp"

class RigidBodyAnimationComponent : public Component {
public:
    RigidBodyAnimationComponent(std::shared_ptr<GameObject> gameObject,
        std::shared_ptr<PhysicsComponent> physicsComponent, Ogre::Entity *entity,
        bool can_attack = true, bool is_boss = false);
    virtual ~RigidBodyAnimationComponent();

    void update (float delta) override;
    int getState () { return _state; };
    Ogre::Vector3 getPosition () { return _physicsComponent->getPosition(); };
    Ogre::Quaternion getOrientation () { return _physicsComponent->getOrientation(); };
    void addToInitialPosition(Ogre::Vector3 quantity);

    enum State {
        SPAWNING,
        ATTACKING,
        DISSAPEARING
    };

protected:
    Ogre::AnimationState *_animation;
    std::shared_ptr<PhysicsComponent> _physicsComponent;
    Ogre::Entity *_entity;
    bool _can_attack;
    int _state;
    Ogre::Bone *_root;
    Ogre::Vector3 _initialPosition;
    bool _active;
    bool _is_boss;
};
