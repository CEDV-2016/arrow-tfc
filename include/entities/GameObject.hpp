#pragma once

#include <vector>
#include <memory>
#include "Component.hpp"
#include <iostream>

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    GameObject() : _is_finished(false) {};
    virtual ~GameObject() {
        _components.clear();
    };

    virtual void update (float delta);
    virtual void removeComponents () { _components.clear(); };
    virtual void finish() { _is_finished = true; };

    void addComponent (std::shared_ptr<Component> component);
    bool isFinished () { return _is_finished; };

    std::shared_ptr<Component> getComponent (int type);

protected:
    std::vector<std::shared_ptr<Component>> _components;
    bool _is_finished;
};
