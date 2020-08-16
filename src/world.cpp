#include "world.h"

#include <iostream>
#include <utility>

World::World(std::string name) :
        name{std::move(name)} {}

World::~World() {
    movables.clear();
    entities.clear();
}

Collisions World::getCollisions() {
    Collisions collisions;
    for (auto e1 : movables) {
        for (auto e2 : entities) {
            if (e1 == e2 || not e1->isCollidable() || not e2->isCollidable())
                continue;
            auto box1 = e1->getBounds();
            auto box2 = e2->getBounds();
            if (box1.intersects(box2)) {
                float distanceX, distanceY = 0;
                float correctionX = 0, correctionY = 0;
                CollisionData::Side side = CollisionData::Side::NONE;
                //TODO: Clean up, this is way to complex than it really needs to be.
                //Check if completely vertical
                if (box1.getLeft() > box2.getLeft() && box1.getRight() < box2.getRight()) {
                    if (box1.getCenter().y > box2.getCenter().y) {
                        distanceY = box2.getBottom() - box1.getTop();
                        correctionY = distanceY;
                        side = CollisionData::Side::TOP;
                    } else {
                        distanceY = box1.getBottom() - box2.getTop();
                        correctionY = -distanceY;
                        side = CollisionData::Side::BOTTOM;
                    }
                } else if (box1.getTop() > box2.getTop() && box1.getBottom() < box2.getBottom()) {
                    if (box1.getCenter().x > box2.getCenter().x) {
                        distanceX = box2.getRight() - box1.getLeft();
                        correctionX = distanceX;
                        side = CollisionData::Side::RIGHT;
                    } else {
                        distanceX = box1.getRight() - box2.getLeft();
                        correctionX = -distanceX;
                        side = CollisionData::Side::LEFT;
                    }
                } else if (box1.getCenter().x > box2.getCenter().x) {
                    if (box1.getCenter().y > box2.getCenter().y) {
                        //Bottom Right corner
                        distanceX = box2.getRight() - box1.getLeft();
                        distanceY = box2.getBottom() - box1.getTop();
                        if (distanceX < distanceY) {
                            correctionX = distanceX;
                            distanceY = correctionY = 0;
                            side = CollisionData::Side::LEFT;
                        } else {
                            correctionX = distanceX = 0;
                            correctionY = distanceY;
                            side = CollisionData::Side::TOP;
                        }
                    } else {
                        //Top Right Corner
                        distanceX = box2.getRight() - box1.getLeft();
                        distanceY = box1.getBottom() - box2.getTop();
                        if (distanceX < distanceY) {
                            correctionX = distanceX;
                            distanceY = correctionY = 0;
                            side = CollisionData::Side::LEFT;
                        } else {
                            correctionX = distanceX = 0;
                            correctionY = -distanceY;
                            side = CollisionData::Side::BOTTOM;
                        }
                    }
                } else {
                    if (box1.getCenter().y > box2.getCenter().y) {
                        //Bottom Left corner
                        distanceX = box1.getRight() - box2.getLeft();
                        distanceY = box2.getBottom() - box1.getTop();
                        if (distanceX < distanceY) {
                            correctionX = -distanceX;
                            distanceY = correctionY = 0;
                            side = CollisionData::Side::RIGHT;
                        } else {
                            correctionX = distanceX = 0;
                            correctionY = distanceY;
                            side = CollisionData::Side::TOP;
                        }
                    } else {
                        //Top Left Corner
                        distanceX = box1.getRight() - box2.getLeft();
                        distanceY = box1.getBottom() - box2.getTop();
                        if (distanceX < distanceY) {
                            correctionX = -distanceX;
                            distanceY = correctionY = 0;
                            side = CollisionData::Side::RIGHT;
                        } else {
                            correctionX = distanceX = 0;
                            correctionY = -distanceY;
                            side = CollisionData::Side::BOTTOM;
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

void World::update(const float &deltaTime) {
    for (auto &e : entities)
        e->update(deltaTime);
}

void World::render(sf::RenderTarget *target) {
    for (const auto &e : entities) {
        e->render(target);
    }
}

void World::addEntity(const StaticEntity &entity) {
    entities.push_back(std::make_shared<StaticEntity>(entity));
}

void World::addEntity(const MovableEntity &entity) {
    auto shared = std::make_shared<MovableEntity>(entity);
    movables.push_back(shared);
    entities.push_back(shared);
}

void World::addPlayer(const Player &entity) {
    player = std::make_shared<Player>(entity);
    movables.push_back(player);
    entities.push_back(player);
}

std::shared_ptr<Entity> World::getPlayer() {
    return player;
}

void World::handleEvent(Event *event) {
    std::cout << "World::handleEvent " + event->ToString() << std::endl;
    std::cout << "World: " + event->ToString() << std::endl;


}

