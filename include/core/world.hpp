#pragma once

#include <memory>
#include <vector>

class Entity;

class World
{
public:
    void update(float dt);

    void addEntity(std::unique_ptr<Entity> e);

    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

private:
    std::vector<std::unique_ptr<Entity>> entities;
};