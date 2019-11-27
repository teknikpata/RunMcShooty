#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "managers/ResourceManager.h"
#include "entities/SceneNode.h"


class Game {
    ResourceManager<sf::Texture, Resources::Textures> textureManager;
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<SceneNode> rootNode;
public:
    Game();
    ~Game();

    void run();
};