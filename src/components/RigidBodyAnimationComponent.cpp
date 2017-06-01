#include "RigidBodyAnimationComponent.hpp"
#include "GameObject.hpp"

RigidBodyAnimationComponent::RigidBodyAnimationComponent(std::shared_ptr<GameObject> gameObject,
    std::shared_ptr<PhysicsComponent> physicsComponent, Ogre::Entity *entity, bool can_attack,
    bool is_boss)
    : Component(gameObject, Component::Type::RIGIDBODYANIMATION), _animation(nullptr),
    _physicsComponent(physicsComponent), _entity(entity), _can_attack(can_attack),
    _state(State::SPAWNING), _root(nullptr), _initialPosition(Ogre::Vector3::ZERO),
    _active(false), _is_boss(is_boss)
{
    _root = _entity->getSkeleton()->getBone("Root");
    _animation = _entity->getAnimationState("SPAWNING");
    _animation->setEnabled(true);
    _animation->setLoop(false);
    _animation->setWeight(1);
    _animation->setTimePosition(0);
    _initialPosition = _physicsComponent->getPosition();
    _physicsComponent->showDebugShape(true);
}

RigidBodyAnimationComponent::~RigidBodyAnimationComponent()
{
    _physicsComponent = nullptr;
}

void RigidBodyAnimationComponent::update(float delta)
{
    _animation->addTime(delta);
    if (!_active) {
        if (_state == State::SPAWNING && _animation->getTimePosition() > 0.3) {
            _initialPosition.x -= 300;
            _active = true;
        }
    }
    if (_animation->hasEnded()) {
        _animation->setEnabled(false);
        _animation->setWeight(0);
        switch (_state) {
            case State::SPAWNING:
                if (_can_attack) {
                    _animation = _entity->getAnimationState("ATTACKING");
                    _state = State::ATTACKING;
                }
                else {
                    _animation = _entity->getAnimationState("DISSAPEARING");
                    _state = State::DISSAPEARING;
                }
                break;
            case State::ATTACKING:
                _animation = _entity->getAnimationState("DISSAPEARING");
                _state = State::DISSAPEARING;
                break;
            case State::DISSAPEARING:
                _gameObject->finish();
                break;
            default:
                break;
        }
        _animation->setEnabled(true);
        _animation->setWeight(1);
        _animation->setTimePosition(0);
        if (!_is_boss) {
            _animation->setLoop(false);
        }
        else {
            _animation->setLoop(true);
        }
    }
    btTransform xForm =_physicsComponent->getTransformation();
    Ogre::Vector3 bonePosition = _root->getPosition();
    Ogre::Quaternion boneOrientation = _root->getOrientation();
    bonePosition += _initialPosition;
    btVector3 position(bonePosition.x, bonePosition.y, bonePosition.z);
    btQuaternion orientation(boneOrientation.x, boneOrientation.y, boneOrientation.z, boneOrientation.w);
    xForm.setOrigin(position);
    xForm.setRotation(orientation);
    _physicsComponent->setTransformation(xForm);
}

void RigidBodyAnimationComponent::addToInitialPosition (Ogre::Vector3 quantity)
{
    _initialPosition += quantity;
}
