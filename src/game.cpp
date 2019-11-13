#include "game.h"

#include <SFML/Window/Event.hpp>
#include "entities/movable_entity.h"
#include "entities/static_entity.h"

Game::Game() {
    window = new sf::RenderWindow(sf::VideoMode(1024, 800), "RunMcShooty");
    Sprite playerSprite{"assets/graphics/player.png", 2, 2, .5f};
    Sprite platformSprite{"assets/graphics/platform.png"};
    Sprite pillarSprite{"assets/graphics/pillar.png"};

    movables.push_back(new MovableEntity(sf::Vector2f(200, 225), true, playerSprite));
    entities.push_back(movables.front());

    entities.push_back(new StaticEntity(sf::Vector2f(200, 265), true, platformSprite));
    entities.push_back(new StaticEntity(sf::Vector2f(400, 400), true, platformSprite));
    entities.push_back(new StaticEntity(sf::Vector2f(200, 400), true, platformSprite));
    entities.push_back(new StaticEntity(sf::Vector2f(0, 400),  true, platformSprite));
    entities.push_back(new StaticEntity(sf::Vector2f(400, 275),  true, pillarSprite));
}

Game::~Game() {
    while (!entities.empty()) {
        delete entities.back();
        entities.pop_back();
    }
    delete window;
}

void Game::run() {
    sf::Clock clock;
    float stepTime = 1.0f / 120.0f;
    float sum = 0.f;
    while (window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sum += deltaTime;
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        if (sum >= stepTime) {
            update(stepTime);
            sum = 0;
        }
        render();
    }
}

Game::Collisions Game::getCollisions() {
    Game::Collisions collisions;
    for (auto e1 : movables) {
        for (auto e2 : entities) {
            if (e1 == e2)
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

                collisions.emplace_back(e1, e2, sf::Vector2f{correctionX, correctionY}, distanceX, distanceY, side);
            }
        }
    }
    return collisions;
}

void Game::resolve(const Game::Collisions &collisions) {
    for (const auto &collision : collisions) {
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

void Game::update(const float &deltaTime) {
    for (auto &e : entities)
        e->update(deltaTime);
    resolve(getCollisions());
    render();
}

void Game::render() {
    window->clear();
    for (auto &e : entities)
        e->render(window);
    window->display();
}