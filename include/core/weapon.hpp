#pragma once

class Player;

class Weapon
{   
public:
    virtual ~Weapon() = default;

    virtual void attack(Player& owner) = 0;
};