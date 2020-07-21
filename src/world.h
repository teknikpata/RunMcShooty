#pragma once

#include "entities/static_entity.h"
#include "entities/movable_entity.h"
#include <memory>

class World {
public:
    struct CollisionData {
        MovableEntity* e1;
        Entity* e2;
        sf::Vector2f depth;
        int distanceX;
        int distanceY;
        CollisionBox::Side side;
        CollisionData(MovableEntity* e1, Entity* e2, sf::Vector2f depth, const int distanceX, const int distanceY,
                      CollisionBox::Side side) :
                e1(e1),
                e2(e2),
                depth(depth),
                distanceX(distanceX),
                distanceY(distanceY),
                side(side) {}

    };
    using Collisions = std::vector<CollisionData>;


    World(const std::string& name) : name{name} {}

    ~World() {
        movables.clear();
        entities.clear();
    };

    Collisions getCollisions() {
        Collisions collisions;
        for (auto e1 : movables) {
            for (auto e2 : entities) {
                if (e1 == e2 || not e2->isCollidable())
                    continue;
                auto box1 = e1->getBounds();
                auto box2 = e2->getBounds();
                if (box1.intersects(box2)) {
                    float distanceX, distanceY = 0;
                    float correctionX = 0, correctionY = 0;
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
    void update(const float& deltaTime) {
        for (auto& e : entities)
            e->update(deltaTime);
    }
    void render(sf::RenderTarget* target) {
        for(const auto& e : entities){
            e->render(target);
        }
    }

    void addEntity(const StaticEntity& entity) {
        entities.push_back(std::make_shared<StaticEntity>(entity));
    }
    void addEntity(const MovableEntity& entity) {
        auto shared = std::make_shared<MovableEntity>(entity);
        movables.push_back(shared);
        entities.push_back(shared);
    }

    void addPlayer(const MovableEntity& entity){
        player = std::make_shared<MovableEntity>(entity);
        movables.push_back(player);
        entities.push_back(player);
    }

    std::shared_ptr<Entity> getPlayer() {
        return player;
    }

    void load(const std::string& filePath) = delete;
    void save() = delete;

private:
    std::string name;
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<MovableEntity>> movables;
    std::shared_ptr<MovableEntity> player;
};

