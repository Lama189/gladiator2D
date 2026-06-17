#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

class Entity;
class Player;

class World
{
public:
    std::unordered_map<std::string, Player*> playerById;
    
    void update(float dt);
    void render();

    void cleanup();

    void addEntity(std::unique_ptr<Entity> e);
    void registerPlayer(const std::string& id, Player* player);

    Player* getPlayerByID(const std::string& id);

    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<std::unique_ptr<Entity>> pendingAdd;

};