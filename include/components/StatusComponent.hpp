#pragma once

#include "Component.hpp"
#include <Ogre.h>

class StatusComponent : public Component
{
public:
    StatusComponent(std::shared_ptr<GameObject> gameObject, int life, int type);
    ~StatusComponent();

    void update (float delta) override;
    void reduceLife(int l);
    void addLife(int l);
    int getLife() { return _life; };
    int getMaxLife() { return _max_life; };
    bool isAlive() { return _life > 0; };
    void setTimeInvulnerable (float time) { _time_invulnerable_remaining = time; };
    float getTimeInvulnerable () { return _time_invulnerable_remaining; };
    int getType() { return _type; };
    float getTimeAlive () { return _time_alive; };

    enum Type {
        PLAYER,
        ENEMY
    };

protected:
    int _life, _type, _max_life;
    float _time_alive, _time_invulnerable_remaining;
    static int _num_active_enemies;
    bool _score_added;
};
