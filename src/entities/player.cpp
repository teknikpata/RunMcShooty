#include "player.h"
#include "player_controller.h"
#include "utils/math.h"
#include <iostream>

Player::Player(const sf::Vector2f &position, const float &speed, const bool collidable,
               const Animator &animator, RestrictedQueue<Event *> eventQueue)
    : weapon{10, 0.05f, 0.2f},
      MovableEntity(position, std::make_shared<PlayerController>(), speed, collidable, animator, eventQueue) {
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
  acceleration = controller->getInput(deltaTime) * speed;
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
