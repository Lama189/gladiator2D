#include "game/weapons/sword/sword.hpp"
#include "game/player.hpp"
#include "game/weapons/sword/swordAttack.hpp"
#include "core/world.hpp"
#include <memory>

void Sword::attack(Player& owner)
{
    auto attack = std::make_unique<SwordAttack>(owner);

    // CAN BE A BAD IDEA
    owner.getWorldFromPlayer().addEntity(std::move(attack));
}