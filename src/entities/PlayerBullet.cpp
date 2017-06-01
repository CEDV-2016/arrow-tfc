#include "PlayerBullet.hpp"
#include "PhysicsComponent.hpp"
#include "NodeComponent.hpp"
#include "StatusComponent.hpp"
#include "ParticlesComponent.hpp"
//#include "SoundComponent.hpp"

void PlayerBullet::initComponents(Ogre::Vector3 position, Ogre::Vector3 direction) {
    std::shared_ptr<NodeComponent> nodeComponent =
        std::make_shared<NodeComponent>(shared_from_this(), "PlayerBullet", _id);
    Ogre::Vector3 velocity_unit = (direction - position).normalisedCopy();
    Ogre::Vector3 velocity = (velocity_unit * PLAYER_BULLET_VELOCITY);
    position += velocity_unit / 2;
    Ogre::Quaternion orientation = Ogre::Vector3(0, 0, 1).getRotationTo((direction - position).normalisedCopy());
    std::shared_ptr<PhysicsComponent> physicsComponent =
        std::make_shared<PhysicsComponent>(shared_from_this(), nodeComponent->getNode(),
        nodeComponent->getEntity(), std::string("PlayerBullet") + std::to_string(_id),
        PhysicsComponent::Type::PLAYER_BULLET, PhysicsComponent::Shape::CAPSULE,
        false, position, Ogre::Vector3(0.3, 1.8, 0), orientation);
    physicsComponent->setLinearVelocity(velocity);
    std::shared_ptr<StatusComponent> statusComponent =
        std::make_shared<StatusComponent>(shared_from_this(), 1, StatusComponent::Type::BULLET);
    std::shared_ptr<ParticlesComponent> partCmp =
        std::make_shared<ParticlesComponent>(shared_from_this(), position,
        ParticlesComponent::Type::PLAYER_LASER, nodeComponent->getNode());
    /*std::shared_ptr<SoundComponent> soundCmp =
        std::make_shared<SoundComponent>(shared_from_this(), SoundComponent::Type::PLAYER_BULLET);*/

    _components.push_back(physicsComponent);
    _components.push_back(nodeComponent);
    _components.push_back(statusComponent);
    _components.push_back(partCmp);
    //_components.push_back(soundCmp);

    ++_id;
}

int PlayerBullet::_id = 0;
