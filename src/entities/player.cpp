#include "player.h"
#include "utils/math.h"
#include <iostream>

Player::Player(const sf::Vector2f &position, const bool collidable,
               const Animator &animator, RestrictedQueue<Event *> eventQueue)
    : weapon{10, 0.05f, 0.2f},
      MovableEntity(position, {}, collidable, animator, eventQueue) {
  speed = 2200.f;
}

Player::~Player() = default;

sf::Vector2f clamp(sf::Vector2f vector, float length) {
  if (math::vectorLength(vector) <= length)
    return sf::Vector2f{0, 0};
  return vector;
}

void Player::update(const float &deltaTime) {
  velocity = clamp(velocity, 10.f);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && weapon.fire()) {
    eventQueue.push(new AttackEvent{getCenter(), {}});
  }

  // TODO: clean this up, this is magic.
  acceleration = getInput() * speed;
  acceleration += -velocity * friction;
  position +=
      (acceleration * 0.85f * (deltaTime * deltaTime)) + (velocity * deltaTime);
  velocity += acceleration * deltaTime;

  setAnimationState();
  setPosition(position);

  animator.update(deltaTime);
  weapon.update(deltaTime);
}

void Player::setAnimationState() {
  if (velocity.x > 0)
    animator.setState(AnimationState::WALKING_RIGHT);
  if (velocity.x < 0)
    animator.setState(AnimationState::WALKING_LEFT);
  if (velocity.y > 0)
    animator.setState(AnimationState::WALKING_DOWN);
  if (velocity.y < 0)
    animator.setState(AnimationState::WALKING_UP);

  if (velocity == sf::Vector2f{0, 0})
    animator.setState(AnimationState::IDLE);
}
sf::Vector2f Player::getInput() {
  sf::Vector2f input = {};
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    input += sf::Vector2f(-1, 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    input += sf::Vector2f(1, 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    input += sf::Vector2f(0, 1);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    input += sf::Vector2f(0, -1);
  }
  return input;
}
