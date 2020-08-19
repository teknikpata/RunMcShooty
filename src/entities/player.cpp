#include <iostream>
#include "player.h"

Player::Player(const sf::Vector2f& position, const bool collidable, const Sprite& sprite,
               RestrictedQueue<Event*> eventQueue) :
              weapon{10, 0.05f, 0.2f},
        MovableEntity(position, {}, collidable, sprite, eventQueue) {
    speed = 2200.f;
}

Player::~Player() = default;

void Player::update(const float& deltaTime) {
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

    weapon.update(deltaTime);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && weapon.fire()) {
        eventQueue.push(new AttackEvent{getCenter(), {}});
    }

    acceleration *= speed;
    acceleration += -velocity * friction;
    position += (acceleration * 0.85f * (deltaTime * deltaTime)) + (velocity * deltaTime);
    velocity += acceleration * deltaTime;
    sprite.update(deltaTime);
    setPosition(position);
}

