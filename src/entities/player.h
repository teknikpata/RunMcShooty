#pragma once

#include "movable_entity.h"

class Player : public MovableEntity {
public:
    Player(const sf::Vector2f &position, bool collidable, const Sprite &sprite, RestrictedQueue<Event *>
    eventQueue);

    ~Player() override;

    void update(const float &deltaTime) override;

protected:
    const int MAX_BULLETS = 3;
    int bullets = MAX_BULLETS;

    const float BULLET_REFILL_TIME = 1;
    float bulletRefillTimer = 0;

    const float WEAPON_COOLDOWN_TIMER = 0.2f;
    float weaponCooldownTimer = 0;
};
