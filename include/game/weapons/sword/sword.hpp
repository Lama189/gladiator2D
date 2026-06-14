#pragma once

#include "core/weapon.hpp"

class Sword : public Weapon
{
public: 
    Sword() = default;

    void attack(Player& owner) override;
};