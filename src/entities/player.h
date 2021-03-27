#pragma once

#include <utils/timer.h>
#include "movable_entity.h"
#include "weapon.h"

class Player : public MovableEntity {
public:
    Player(const sf::Vector2f& position, bool collidable, const Sprite& sprite, RestrictedQueue<Event*>
    eventQueue);

    ~Player() override;

    void update(const float& deltaTime) override;

protected:
    Weapon weapon;
};
