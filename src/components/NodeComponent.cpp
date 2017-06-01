#include "NodeComponent.hpp"
#include "StatusComponent.hpp"
#include "GameObject.hpp"

NodeComponent::NodeComponent (std::shared_ptr<GameObject> gameObject,
  std::string mesh_name, int id, bool setCastShadows)
  : Component(gameObject, Component::Type::NODE), _node(nullptr), _entity(nullptr),
  _sceneMgr(nullptr), _damaged(false), _time_damaged(0), _time(0)
{
    _sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("SceneManager");
    _entity = _sceneMgr->createEntity(mesh_name + std::string("Entity") + std::to_string(id), mesh_name + std::string(".mesh"));
    _node = _sceneMgr->createSceneNode(mesh_name + std::to_string(id));
    _sceneMgr->getRootSceneNode()->addChild(_node);
    _node->attachObject(_entity);
    _entity->setCastShadows(setCastShadows);
    _node->setVisible(true);
}

NodeComponent::~NodeComponent ()
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
}

Ogre::Vector3 NodeComponent::getPosition ()
{
    if (_node) {
        return _node->getPosition();
    }
    return Ogre::Vector3();
}

Ogre::Quaternion NodeComponent::getOrientation ()
{
    if (_node) {
        return _node->getOrientation();
    }
    return Ogre::Quaternion();
}

void NodeComponent::changeToDamagedMaterial ()
{
    _time_damaged = _time;
    _damaged = true;
    _entity->setMaterialName("Material_Enemy_Damaged");
}

void NodeComponent::update (float delta)
{
    _time += delta;
    if (_damaged) {
        if (_time - _time_damaged > MAX_TIME_DAMAGED) {
            _damaged = false;
            std::string material;
            switch (std::static_pointer_cast<StatusComponent>(_gameObject->getComponent(Component::Type::STATUS))->getType()) {
                case StatusComponent::Type::ENEMY:
                    material = std::string("Material_Enemy");
                    break;
                case StatusComponent::Type::PLAYER:
                    material = std::string("Player");
                    break;
                default:
                    return;
                    break;
            }
            _entity->setMaterialName(material);
        }
    }
}

const float NodeComponent::MAX_TIME_DAMAGED = 0.02;
