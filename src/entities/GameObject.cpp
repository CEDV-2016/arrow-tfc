#include "GameObject.hpp"

void GameObject::update (float delta)
{
    int size = _components.size();
    for (int i = 0; i < size; ++i) {
        _components[i]->update(delta);
        if (_components[i]->isFinished()) {
            _components.erase(_components.begin() + i);
            --i; --size;
        }
    }
}

void GameObject::addComponent (std::shared_ptr<Component> component)
{
    _components.push_back(component);
}

std::shared_ptr<Component> GameObject::getComponent(int type)
{
    int size = _components.size();
    for (int i = 0; i < size; ++i) {
        if (_components[i]->getType() == type) {
            return _components[i];
        }
    }
    return nullptr;
}
