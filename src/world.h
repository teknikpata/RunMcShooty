#pragma once

#include "entities/static_entity.h"
#include "entities/movable_entity.h"
#include "entities/player.h"
#include "utils/collision_data.h"
#include "events/event.h"
#include <memory>

class World {
public:
    explicit World(std::string name);

    ~World();

    Collisions getCollisions();

    void update(const float &deltaTime);

    void render(sf::RenderTarget *target);

    void addEntity(const StaticEntity &entity);

    void addEntity(const MovableEntity &entity);

    void addPlayer(const Player &entity);

    std::shared_ptr<Entity> getPlayer();

    void handleEvent(Event *event);

    void load(const std::string &filePath) = delete;

    void save() = delete;

private:
    std::string name;
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<MovableEntity>> movables;
    std::shared_ptr<Player> player;
};

