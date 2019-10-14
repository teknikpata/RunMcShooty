#include "game.h"
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <iostream>
#include "movable_entity.h"

Game::Game() {
    window = new sf::RenderWindow(sf::VideoMode(1024, 800), "RunMcShooty");
    movables.push_back(new MovableEntity(sf::Vector2f(200, 225), sf::Vector2f(50, 50)));
    entities.push_back(movables.front());
    entities.push_back(new Entity(sf::Vector2f(0, 265), sf::Vector2f(75, 50)));
    entities.push_back(new Entity(sf::Vector2f(600, 225), sf::Vector2f(100, 600)));
    entities.push_back(new Entity(sf::Vector2f(0, 275), sf::Vector2f(600, 50)));
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
    float stepTime = 1.0f / 60.0f;
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
                auto midPoint1 = box1.getMiddlePoint();
                auto midPoint2 = box2.getMiddlePoint();
                float distanceX, distanceY = 0;
                float correctionX, correctionY = 0;

                if (midPoint1.x > midPoint2.x) {
                } else if (midPoint1.x < midPoint2.x) {
                }

                if (midPoint1.y < midPoint2.y) {
                } else if (midPoint1.y > midPoint2.y) {
                }

                /*if (midPoint1.x > midPoint2.x) {
				    std::cout << "1" << std::endl;
					distanceX = std::abs(box1.getLeft() - box2.getRight());
					correctionX = distanceX;
				}
				else if (midPoint1.x < midPoint2.x) {
                    std::cout << "2" << std::endl;
				    distanceX = std::abs(box1.getRight() - box2.getLeft());
					correctionX = -distanceX;
				}

				if (midPoint1.y < midPoint2.y) {
                    std::cout << "3" << std::endl;
					distanceY = std::abs(box2.getTop() - box1.getBottom());
					correctionY = -distanceY;
				}
				else if (midPoint1.y > midPoint2.y) {
                    std::cout << "4" << std::endl;
					distanceY = std::abs(box1.getTop() - box2.getBottom());
					correctionY = distanceY;
				}*/
                printf("Found collision; DistanceX: %.3f, DistanceY: %.3f, CorrectionX: %.3f, CorrectionY: %.3f",
                       distanceX, distanceY, correctionX, correctionY);
                collisions.emplace_back(e1, e2, sf::Vector2f{correctionX, correctionY}, distanceX, distanceY);
            }
        }
    }
    return collisions;
}

Game::Collisions Game::getHorizontalCollisions() {
    Game::Collisions collisions;
    for (auto e1 : movables) {
        for (auto e2 : entities) {
            if (e1 == e2)
                continue;

            auto box1 = e1->getBounds();
            auto box2 = e2->getBounds();
            // checking for collision horizontally
            if (box1.intersects(box2)) {
                auto midPoint1 = box1.getMiddlePoint();
                auto midPoint2 = box2.getMiddlePoint();

                if (midPoint1.x > midPoint2.x) {
                    auto correction = box2.getRight() - box1.getLeft();
                    auto position = e1->getPosition();
                    collisions.emplace_back(e1, e2, sf::Vector2f{correction, 0}, 0, 0);
                    e1->multiplyVelocity({0, 1});
                    std::cout << "Collision on Left Side" << std::endl;
                    printf("Correction: %f \n", correction);
                }
                if (midPoint1.x < midPoint2.x) {
                    auto correction = box1.getRight() - box2.getLeft();
                    auto position = e1->getPosition();
                    e1->multiplyVelocity({0, 1});
                    collisions.emplace_back(e1, e2, sf::Vector2f{-correction, 0}, 0, 0);
                    std::cout << "Collision on Right Side" << std::endl;
                    printf("Correction: %f \n", correction);
                }
            }
        }
    }
    return collisions;
}

Game::Collisions Game::getVerticalCollisions() {
    Game::Collisions collisions;
    for (auto e1 : movables) {
        for (auto e2 : entities) {
            if (e1 == e2)
                continue;

            auto box1 = e1->getBounds();
            auto box2 = e2->getBounds();
            // checking for collision vertically
            if (box1.intersects(box2)) {
                auto midPoint1 = box1.getMiddlePoint();
                auto midPoint2 = box2.getMiddlePoint();

                if (midPoint1.y < midPoint2.y) {
                    auto correction = box2.getTop() - box1.getBottom();
                    auto position = e1->getPosition();
                    collisions.emplace_back(e1, e2, sf::Vector2f{0, correction}, 0, 0);
                    e1->multiplyVelocity({1, 0});
                    std::cout << "Collision on Bottom Side" << std::endl;
                    printf("Correction: %f \n", correction);
                }
                if (midPoint1.y > midPoint2.y) {
                    auto correction = box1.getTop() - box2.getBottom();
                    auto position = e1->getPosition();
                    collisions.emplace_back(e1, e2, sf::Vector2f{0, -correction}, 0, 0);
                    e1->multiplyVelocity({1, 0});
                    std::cout << "Collision on Top Side" << std::endl;
                    printf("Correction: %f \n", correction);
                }
            }
        }
        break;
    }
    return collisions;
}

void Game::resolve(const Game::Collisions &collisions) {
    for (const auto &collision : collisions) {
        auto movEntity = collision.e1;
        auto timeX = collision.distanceX / movEntity->getVelocity().x;
        auto timeY = collision.distanceY / movEntity->getVelocity().y;

        if (timeX > timeY) {
            movEntity->move(collision.depth);
            std::cout << "Horizontal collision" << std::endl;
        } else if (timeY > timeX) {
            std::cout << "Vertical collision" << std::endl;
            movEntity->move(collision.depth);
            movEntity->multiplyVelocity(sf::Vector2f(1.f, 0.f));
        }

        // else
        //collided in corner
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
