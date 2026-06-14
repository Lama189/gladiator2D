#include "core/world.hpp"
#include "core/entity.hpp"
#include <algorithm>

void World::update(float dt)
{
    for (auto& entity : entities)
        entity->update(dt);

    entities.erase(std::remove_if(entities.begin(), entities.end(),
        [](const auto& e)
        {
            return !e->alive();
        }
    ), entities.end());
}

void World::addEntity(std::unique_ptr<Entity> e)
{
    entities.push_back(std::move(e));
}

const std::vector<std::unique_ptr<Entity>>& World::getEntities() const
{
    return entities;
}