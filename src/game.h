#pragma once

#include "entities/entity.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "entities/movable_entity.h"
#include "utils/camera.h"
#include "world.h"
#include "events/event.h"

#include <queue>

class Game {
public:
    Game();
    ~Game();

    void run();

private:
    void update(const float& deltaTime);
    void render();
    void resolve(const Collisions& collisions);
    World world;
    Camera camera;
    sf::RenderWindow* window;

    std::queue<Event*> eventQueue;
};