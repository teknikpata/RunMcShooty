#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "utils/camera.h"
#include "world.h"
#include "events/event.h"
#include "managers/texture_manager.h"

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

    void initializeResources();

    void createWorld();

    World world;
    Camera camera;
    sf::RenderWindow* window;
    TextureManager textureManager;

    std::queue<Event*> eventQueue;
};