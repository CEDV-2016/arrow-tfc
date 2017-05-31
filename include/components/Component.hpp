#pragma once

#include <memory>

class GameObject;

class Component {
public:
    /// Constructor
    Component(std::shared_ptr<GameObject> gameObject, int type) : _gameObject(gameObject), _type(type){};
    /// Destructor
    virtual ~Component() {
        _gameObject = nullptr;
    };

    /**
     * This virtual method is called every frame by it's owner GameObject. It
     * will be overwritten by the Component which inherits from it. */
    virtual void update(float deltaT) {};

    /// Returns the type of the Component
    int getType () { return _type; };

    /// Returns if the GameObject has ended or not
    virtual bool isFinished () { return false; };

    /// Types of Component
    enum Type {
        STATUS,
        RIGIDBODYANIMATION,
    };

protected:
    /// GameObject owner of this Component
    std::shared_ptr<GameObject> _gameObject;
    /// Type of the Component
    int _type;
};
