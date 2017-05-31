#pragma once

#include <memory>

class GameObject;

class Component
{
public:
    Component(std::shared_ptr<GameObject> gameObject, int type) : _gameObject(gameObject), _type(type){};
    virtual ~Component() {
        _gameObject = nullptr;
    };

    virtual void update(float deltaT) {};
    virtual bool isFinished () { return false; };

    int getType () { return _type; };

    enum Type {
        PARTICLES,
        STATUS,
        RIGIDBODYANIMATION,
    };

protected:
    std::shared_ptr<GameObject> _gameObject;
    int _type;
};
