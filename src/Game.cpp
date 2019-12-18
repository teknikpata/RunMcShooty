#include "Game.h"

#include <SFML/Window/Event.hpp>
#include "entities/Entitiy.h"
#include "entities/SpriteNode.h"

const auto TimePerFrame = sf::seconds(1.0f / 60.f);

Game::Game() {
    window =  std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 800), "RunMcShooty");
    textureManager.load(Resources::Textures::Player, "assets/graphics/player.png");
    textureManager.load(Resources::Textures::Platform, "assets/graphics/platform.png");
    textureManager.load(Resources::Textures::Pillar, "assets/graphics/pillar.png");
    rootNode = std::make_unique<SceneNode>();
    for(int i = 0; i < LayerCount; ++i) {
        auto layerNode = std::make_unique<SceneNode>();
        layers[i] = layerNode.get();
        rootNode->addChild(std::move(layerNode));
    }

    auto e1 = std::make_unique<Entity>(sf::Vector2f{static_cast<float>(window->getSize().x) / 2, static_cast<float>(window->getSize().y) / 2}, Entity::Type::Player, textureManager);
    player = e1.get();
    layers[WorldLayers::Foreground]->addChild(std::move(e1));

    sf::Texture& texture = textureManager.get(Resources::Textures::Pillar);
    sf::IntRect textureRect(200, 200, 1200, 1200);
    texture.setRepeated(true);
    auto background = std::make_unique<SpriteNode>(texture, textureRect);
    layers[WorldLayers::Background]->addChild(std::move(background));
}
Game::~Game() = default;

void Game::run() {
    sf::Clock clock;
    auto lastUpdate = sf::Time::Zero;
    while (window->isOpen()) {
        handleInput();
        lastUpdate += clock.restart();
        while(lastUpdate > TimePerFrame){
            lastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame.asSeconds());
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Game::handleInput() {
    input = sf::Vector2f{0.f, 0.f};
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        input +=sf::Vector2f{0.f, -1.f};
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        input +=sf::Vector2f{0.f, 1.f};
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        input +=sf::Vector2f{-1.f, 0.f};
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        input +=sf::Vector2f{1.f, 0.f};
    }
}

void Game::render() {
    window->clear();
    window->draw(*rootNode);
    window->display();
}

void Game::update(const float deltaTime) {
    player->accelerate(input);
    rootNode->update(deltaTime);
}

void Game::handleCollisions() {
    for(auto& entity : )
}
