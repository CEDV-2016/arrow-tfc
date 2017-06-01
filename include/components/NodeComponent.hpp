#pragma once

#include "Component.hpp"
#include <Ogre.h>

class NodeComponent : public Component
{
public:
    NodeComponent(std::shared_ptr<GameObject> gameObject, std::string mesh_name, int id, bool setCastShadows = true);
    virtual ~NodeComponent();

    Ogre::Vector3 getPosition ();
    Ogre::Quaternion getOrientation ();
    Ogre::Entity* getEntity () { return _entity; };
    Ogre::SceneNode* getNode () { return _node; };

    void changeToDamagedMaterial ();
    void update (float delta) override;

    static const float MAX_TIME_DAMAGED;

protected:
    Ogre::SceneNode *_node;
    Ogre::Entity *_entity;
    Ogre::SceneManager *_sceneMgr;
    bool _damaged;
    float _time_damaged, _time;
};
