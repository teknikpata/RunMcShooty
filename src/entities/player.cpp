#include <iostream>
#include <math.h>
#include "player.h"

Player::Player(const sf::Vector2f &position, const bool collidable, const Sprite &sprite,
               RestrictedQueue<Event *> eventQueue) :
        MovableEntity(position, {}, collidable, sprite, eventQueue) {
}

Player::~Player() = default;

void Player::update(const float &deltaTime) {
    acceleration = {};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        acceleration += sf::Vector2f(-1, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        acceleration += sf::Vector2f(1, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        acceleration += sf::Vector2f(0, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        acceleration += sf::Vector2f(0, -1);
    }

    if (weaponCooldownTimer >= 0) {
        weaponCooldownTimer -= deltaTime;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && bullets > 0 && weaponCooldownTimer <= 0) {
        auto direction = sf::Mouse::getPosition() - static_cast<sf::Vector2i>(position);
        float pX = powf(position.x, 2);
        float pY = powf(position.y, 2);
        auto length = sqrtf(pX + pY);
        auto normalizedDirection = sf::Vector2f{0,0};
        if (length != 0) {
            normalizedDirection = sf::Vector2f{direction.x / length, direction.y / length};
        }


        eventQueue.push(new AttackEvent{position, normalizedDirection});
        bullets--;
        weaponCooldownTimer = WEAPON_COOLDOWN_TIMER;
    }

    bulletRefillTimer -= deltaTime;
    if (bulletRefillTimer <= 0 && bullets < MAX_BULLETS) {
        bullets++;
        bulletRefillTimer = BULLET_REFILL_TIME;
    }

    acceleration *= speed;
    acceleration += -velocity * friction;
    position += (acceleration * 0.85f * (deltaTime * deltaTime)) + (velocity * deltaTime);
    velocity += acceleration * deltaTime;
    sprite.update(deltaTime);
    setPosition(position);
}

