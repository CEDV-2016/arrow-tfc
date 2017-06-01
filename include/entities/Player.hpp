#pragma once

#include "GameObject.hpp"

class Player : public GameObject
{
public:
    Player() : GameObject() {};
    virtual ~Player();

    void initComponents ();
    void removeComponents () override;
    void visibilityEyehole(bool visibility);
    void visibilityHUD(bool visibility);

protected:
    int _id_player;
    static unsigned int _number_of_players_created;
};
