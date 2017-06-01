#include <memory>
#include "Player.hpp"
//#include "InputComponent.h"
//#include "InputMouseComponent.h"
//#include "InputJoystickComponent.h"
#include "NodeComponent.hpp"
#include "PhysicsComponent.hpp"
#include "StatusComponent.hpp"
//#include "CEGUIComponent.h"
#include "CameraManager.hpp"
#include "ParticlesComponent.hpp"

Player::~Player() {
}

void Player::initComponents () {
    std::shared_ptr<NodeComponent> nodeComponent;
    nodeComponent = std::make_shared<NodeComponent>(shared_from_this(), "Arrow", 1);

    std::shared_ptr<PhysicsComponent> physicsComponent =
        std::make_shared<PhysicsComponent>(shared_from_this(), nodeComponent->getNode(),
        nodeComponent->getEntity(), std::string("Arrow"), PhysicsComponent::Type::PLAYER,
        PhysicsComponent::Shape::CONVEX, true, Ogre::Vector3(0, 0, -10));
    std::shared_ptr<StatusComponent> statusComponent;

    statusComponent = std::make_shared<StatusComponent>(shared_from_this(), 10, StatusComponent::Type::PLAYER);

    physicsComponent->setStatusComponent(statusComponent);
    Ogre::Node *propeller = nodeComponent->getNode();
    std::shared_ptr<ParticlesComponent> partCmp1;
    std::shared_ptr<ParticlesComponent> partCmp2;

    /*partCmp1 = std::make_shared<ParticlesComponent>(shared_from_this(), propeller->getPosition(),
        ParticlesComponent::Type::PLAYERPROPULSION, propeller,
        Ogre::Vector3(0.285314, -0.054088, 0.809459), Ogre::Vector3(0, 0, 1));
    partCmp2 = std::make_shared<ParticlesComponent>(shared_from_this(), propeller->getPosition(),
        ParticlesComponent::Type::PLAYERPROPULSION, propeller,
        Ogre::Vector3(-0.285314, -0.054088, 0.809459), Ogre::Vector3(0, 0, 1));

    std::shared_ptr<ParticlesComponent> partCmp3 =
        std::make_shared<ParticlesComponent>(shared_from_this(), propeller->getPosition(),
        ParticlesComponent::Type::WINGS_FRICTION, propeller, Ogre::Vector3(-0.95, -0.052088, 1.309459));
    std::shared_ptr<ParticlesComponent> partCmp4 =
        std::make_shared<ParticlesComponent>(shared_from_this(), propeller->getPosition(),
        ParticlesComponent::Type::WINGS_FRICTION, propeller, Ogre::Vector3(0.95, -0.052088, 1.309459));
    std::shared_ptr<ParticlesComponent> partCmp5 =
        std::make_shared<ParticlesComponent>(shared_from_this(), propeller->getPosition(),
        ParticlesComponent::Type::WINGS_FRICTION, propeller, Ogre::Vector3(-0.31, 0.401088, 1.709459));
    std::shared_ptr<ParticlesComponent> partCmp6 =
        std::make_shared<ParticlesComponent>(shared_from_this(), propeller->getPosition(),
        ParticlesComponent::Type::WINGS_FRICTION, propeller, Ogre::Vector3(0.31, 0.401088, 1.709459));*/
    _components.push_back(physicsComponent);
    _components.push_back(nodeComponent);
    _components.push_back(statusComponent);
    /*_components.push_back(partCmp1);
    _components.push_back(partCmp2);
    _components.push_back(partCmp3);
    _components.push_back(partCmp4);
    _components.push_back(partCmp5);
    _components.push_back(partCmp6);*/

    //CameraManager::getSingletonPtr()->addPlayer(nodeComponent->getNode(), _number_of_players_created);
    _id_player = _number_of_players_created;
    ++_number_of_players_created;
}

void Player::removeComponents () {
    GameObject::removeComponents();
    //CameraManager::getSingletonPtr()->removePlayer(_id_player);
}

void Player::visibilityEyehole(bool visibility){
    //std::static_pointer_cast<InputComponent>(shared_from_this()->getComponent(Component::Type::INPUT))->visibilityEyehole(visibility);
}

void Player::visibilityHUD(bool visibility){
    //std::static_pointer_cast<CEGUIComponent>(shared_from_this()->getComponent(Component::Type::CEGUI))->visibilityHUD(visibility);
}

unsigned int Player::_number_of_players_created = 1;
