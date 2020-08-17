#include <iostream>
#include "player.h"

Player::Player(const sf::Vector2f& position, const bool collidable, const Sprite& sprite,
               RestrictedQueue<Event*> eventQueue) :
               timerRefill{1.f, "timerRefill"},
               timerCooldown{0.2f, "timerCooldown"},
        MovableEntity(position, {}, collidable, sprite, eventQueue) {
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

    timerCooldown.update(deltaTime);
    timerRefill.update(deltaTime);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && bullets > 0 && timerCooldown.done()) {
        eventQueue.push(new AttackEvent{getCenter(), {}});
        bullets--;
        timerCooldown.reset();
    }

    if (timerRefill.done() && bullets < MAX_BULLETS) {
        bullets++;
        timerRefill.reset();
    }

    acceleration *= speed;
    acceleration += -velocity * friction;
    position += (acceleration * 0.85f * (deltaTime * deltaTime)) + (velocity * deltaTime);
    velocity += acceleration * deltaTime;
    sprite.update(deltaTime);
    setPosition(position);
}

