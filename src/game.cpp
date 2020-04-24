#include "game.h"

#include <SFML/Window/Event.hpp>
#include "entities/movable_entity.h"
#include "entities/static_entity.h"
#include "managers/texture_manager.h"
#include "utils/camera.h"


const auto TimePerFrame = sf::seconds(1.0f / 60.f);
constexpr int HEIGHT = 800;
constexpr int WIDTH = 1200;

Game::Game() :
        camera{} {
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "RunMcShooty");
    TextureManager textureManager;

    textureManager.load("player", "assets/graphics/player.png");
    textureManager.load("platform", "assets/graphics/platform.png");
    textureManager.load("pillar", "assets/graphics/pillar.png");

    Sprite playerSprite{textureManager.get("player"), 2, 2, 1.f};
    Sprite platformSprite{textureManager.get("platform")};
    Sprite pillarSprite{textureManager.get("pillar")};

    movables.push_back(std::make_shared<MovableEntity>(sf::Vector2f(200, 225), true, playerSprite));
    entities.push_back(movables.front());
    camera.follow(movables.front(),{300, 200} );
    entities.push_back(std::make_shared<StaticEntity>(sf::Vector2f{200, 265}, true, platformSprite));
    entities.push_back(std::make_shared<StaticEntity>(sf::Vector2f{401, 400}, true, platformSprite));
    entities.push_back(std::make_shared<StaticEntity>(sf::Vector2f{0, 400}, true, platformSprite));
    entities.push_back(std::make_shared<StaticEntity>(sf::Vector2f{0, 400}, true, platformSprite));
    entities.push_back(std::make_shared<StaticEntity>(sf::Vector2f{400, 275}, false, pillarSprite));
}

Game::~Game() {
    movables.clear();
    entities.clear();
    delete window;
}

void Game::run() {
    sf::Clock clock;
    auto lastUpdate = sf::Time::Zero;
    while (window->isOpen()) {
        lastUpdate += clock.restart();
        while (lastUpdate > TimePerFrame) {
            lastUpdate -= TimePerFrame;
            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
            }
            update(TimePerFrame.asSeconds());
        }
        render();
    }
}

Game::Collisions Game::getCollisions() {
    Game::Collisions collisions;
    for (auto e1 : movables) {
        for (auto e2 : entities) {
            if (e1 == e2 || not e2->isCollidable())
                continue;
            auto box1 = e1->getBounds();
            auto box2 = e2->getBounds();
            if (box1.intersects(box2)) {
                float distanceX, distanceY = 0;
                float correctionX, correctionY = 0;
                CollisionBox::Side side = CollisionBox::Side::NONE;
                //TODO: Clean up, this is way to complex than it really needs to be.
                //Check if completely vertical
                if (box1.getLeft() > box2.getLeft() && box1.getRight() < box2.getRight()) {
                    if (box1.getMiddlePoint().y > box2.getMiddlePoint().y) {
                        distanceY = box2.getBottom() - box1.getTop();
                        correctionY = distanceY;
                        side = CollisionBox::Side::TOP;
                    } else {
                        distanceY = box1.getBottom() - box2.getTop();
                        correctionY = -distanceY;
                        side = CollisionBox::Side::BOTTOM;
                    }
                } else if (box1.getTop() > box2.getTop() && box1.getBottom() < box2.getBottom()) {
                    if (box1.getMiddlePoint().x > box2.getMiddlePoint().x) {
                        distanceX = box2.getRight() - box1.getLeft();
                        correctionX = distanceX;
                        side = CollisionBox::Side::RIGHT;
                    } else {
                        distanceX = box1.getRight() - box2.getLeft();
                        correctionX = -distanceX;
                        side = CollisionBox::Side::LEFT;
                    }
                } else if (box1.getMiddlePoint().x > box2.getMiddlePoint().x) {
                    if (box1.getMiddlePoint().y > box2.getMiddlePoint().y) {
                        //Bottom Right corner
                        distanceX = box2.getRight() - box1.getLeft();
                        distanceY = box2.getBottom() - box1.getTop();
                        if (distanceX < distanceY) {
                            correctionX = distanceX;
                            distanceY = correctionY = 0;
                            side = CollisionBox::Side::LEFT;
                        } else {
                            correctionX = distanceX = 0;
                            correctionY = distanceY;
                            side = CollisionBox::Side::TOP;
                        }
                    } else {
                        //Top Right Corner
                        distanceX = box2.getRight() - box1.getLeft();
                        distanceY = box1.getBottom() - box2.getTop();
                        if (distanceX < distanceY) {
                            correctionX = distanceX;
                            distanceY = correctionY = 0;
                            side = CollisionBox::Side::LEFT;
                        } else {
                            correctionX = distanceX = 0;
                            correctionY = -distanceY;
                            side = CollisionBox::Side::BOTTOM;
                        }
                    }
                } else {
                    if (box1.getMiddlePoint().y > box2.getMiddlePoint().y) {
                        //Bottom Left corner
                        distanceX = box1.getRight() - box2.getLeft();
                        distanceY = box2.getBottom() - box1.getTop();
                        if (distanceX < distanceY) {
                            correctionX = -distanceX;
                            distanceY = correctionY = 0;
                            side = CollisionBox::Side::RIGHT;
                        } else {
                            correctionX = distanceX = 0;
                            correctionY = distanceY;
                            side = CollisionBox::Side::TOP;
                        }
                    } else {
                        //Top Left Corner
                        distanceX = box1.getRight() - box2.getLeft();
                        distanceY = box1.getBottom() - box2.getTop();
                        if (distanceX < distanceY) {
                            correctionX = -distanceX;
                            distanceY = correctionY = 0;
                            side = CollisionBox::Side::RIGHT;
                        } else {
                            correctionX = distanceX = 0;
                            correctionY = -distanceY;
                            side = CollisionBox::Side::BOTTOM;
                        }
                    }
                }
                // TODO: Dont take raw pointer.
                collisions.emplace_back(e1.get(), e2.get(), sf::Vector2f{correctionX, correctionY}, distanceX,
                        distanceY,
                        side);
            }
        }
    }
    return collisions;
}

void Game::resolve(const Game::Collisions& collisions) {
    for (const auto& collision : collisions) {
        auto e1Bounds = collision.e1->getBounds();
        auto e2Bounds = collision.e2->getBounds();

        //Check if collision is already solved
        if (!e1Bounds.intersects(e2Bounds))
            continue;

        auto movEntity = collision.e1;
        movEntity->move(collision.depth);
        if (collision.side == CollisionBox::Side::RIGHT || collision.side == CollisionBox::Side::LEFT) {
            movEntity->multiplyVelocity(sf::Vector2f(0.f, 1.f));
        } else if (collision.side == CollisionBox::Side::TOP) {
            movEntity->multiplyVelocity(sf::Vector2f(1.f, 0.f));
        } else if (collision.side == CollisionBox::Side::BOTTOM) {
            movEntity->multiplyVelocity(sf::Vector2f(1.f, 0.f));
            movEntity->notifyGrounded();
        }
    }
}

void Game::update(const float& deltaTime) {
    for (auto& e : entities)
        e->update(deltaTime);
    resolve(getCollisions());
    const auto& player = movables.front();

    window->setView(camera(window->getView()));
    render();
}

void Game::render() {
    window->clear();
    for (auto& e : entities)
        e->render(window);
    window->display();
}