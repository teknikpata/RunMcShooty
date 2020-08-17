#pragma once

#include <SFML/System/Vector2.hpp>

class MovableEntity;

class Entity;

struct CollisionData {
    enum class Side {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
        NONE
    };

    MovableEntity* e1;
    Entity* e2;
    sf::Vector2f depth;
    int distanceX;
    int distanceY;
    Side side;

    CollisionData(MovableEntity* e1, Entity* e2, const sf::Vector2f& depth, const int distanceX, const int distanceY,
                  Side side) :
            e1(e1)
            , e2(e2)
            , depth(depth)
            , distanceX(distanceX)
            , distanceY(distanceY)
            , side(side) {}

};

using Collisions = std::vector<CollisionData>;
