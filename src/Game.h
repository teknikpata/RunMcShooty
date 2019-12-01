#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "entities/Entitiy.h"
#include "managers/ResourceManager.h"
#include "entities/SceneNode.h"


class Game {
    ResourceManager<sf::Texture, Resources::Textures> textureManager;
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<SceneNode> rootNode;
    Entity* player;
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void handleInput();
    void render();
    void update(float deltaTime);
    sf::Vector2f input;
};