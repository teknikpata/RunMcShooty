#pragma once

#include "movable_entity.h"
#include "weapon.h"
#include <utils/timer.h>

class Player : public MovableEntity {
public:
  Player(const sf::Vector2f &position, bool collidable,
         const Animator &animator, RestrictedQueue<Event *> eventQueue);

  ~Player() override;

  void update(const float &deltaTime) override;

protected:
  Weapon weapon;

private:
  sf::Vector2f getInput();
  void setAnimationState();
};
