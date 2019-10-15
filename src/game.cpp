#include "game.h"

#include <SFML/Window/Event.hpp>
#include "movable_entity.h"

Game::Game() {
    window = new sf::RenderWindow(sf::VideoMode(1024, 800), "RunMcShooty");
    movables.push_back(new MovableEntity(sf::Vector2f(200, 225), sf::Vector2f(50, 50)));
    entities.push_back(movables.front());
    entities.push_back(new Entity(sf::Vector2f(0, 265), sf::Vector2f(75, 50)));
    entities.push_back(new Entity(sf::Vector2f(400, 175), sf::Vector2f(100, 600)));
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
                float distanceX, distanceY = 0;
                float correctionX, correctionY = 0;

                //Check if completely vertical
                if(box1.getLeft() > box2.getLeft() && box1.getRight() < box2.getRight()) {
                    printf("Completely Vertical Collision \n");
                    // TODO: Move to resolve collisions
                    e1->multiplyVelocity(sf::Vector2f(1.f, 0.f));
                    if(box1.getMiddlePoint().y > box2.getMiddlePoint().y) {
                        distanceY = box2.getBottom() - box1.getTop();
                        correctionY = distanceY;
                    }
                    else {
                        distanceY = box1.getBottom() - box2.getTop();
                        correctionY = -distanceY;
                    }
                }
                if(box1.getTop() > box2.getTop() && box1.getBottom() < box2.getBottom()) {
                    printf("Completely Horizontal Collision \n");
                    //TODO: move to resolve collisions
                    e1->multiplyVelocity(sf::Vector2f(0.f, 1.f));
                    if(box1.getMiddlePoint().x > box2.getMiddlePoint().x) {
                        distanceX = box2.getRight() - box1.getLeft();
                        correctionX = distanceX;
                    }
                    else {
                        distanceX = box1.getRight() - box2.getLeft();
                        correctionX = -distanceX;
                    }
                }
                //corner collision.
                collisions.emplace_back(e1, e2, sf::Vector2f{correctionX, correctionY}, distanceX, distanceY);
            }
        }
    }
    return collisions;
}

void Game::resolve(const Game::Collisions &collisions) {
    for (const auto &collision : collisions) {
        auto movEntity = collision.e1;
        //auto timeX = collision.distanceX / movEntity->getVelocity().x;
        //auto timeY = collision.distanceY / movEntity->getVelocity().y;
        // if (timeX > timeY) {
            movEntity->move(collision.depth);
        // } else if (timeY > timeX) {
        //     std::cout << "Vertical collision" << std::endl;
        //     movEntity->move(collision.depth);
        //     movEntity->multiplyVelocity(sf::Vector2f(1.f, 0.f));
        // }

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