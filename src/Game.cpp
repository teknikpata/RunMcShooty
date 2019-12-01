#include "Game.h"

#include <SFML/Window/Event.hpp>
#include <iostream>
#include "entities/Entitiy.h"


Game::Game() {
    window =  std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 800), "RunMcShooty");

    textureManager.load(Resources::Textures::Player, "assets/graphics/player.png");
    textureManager.load(Resources::Textures::Platform, "assets/graphics/platform.png");
    textureManager.load(Resources::Textures::Pillar, "assets/graphics/pillar.png");
    rootNode = std::make_unique<SceneNode>();
    auto e1 = std::make_unique<Entity>(sf::Vector2f{400, 400}, Entity::Type::Player, textureManager);
    rootNode->addChild(std::move(e1));
}

Game::~Game() {
}

void Game::run() {
    sf::Clock clock;
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        rootNode->update(clock.restart().asSeconds());
        window->clear();
        window->draw(*rootNode);
        window->display();
    }
}