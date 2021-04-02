#pragma once

#include "entity.h"

class MovableEntity : public Entity {
public:
  MovableEntity(const sf::Vector2f &position, const sf::Vector2f &velocity,
                bool collidable, const Animator &animator,
                RestrictedQueue<Event *> eventQueue);

  ~MovableEntity() override;
  void update(const float &deltaTime) override;
  void render(sf::RenderTarget *renderTarget) override;

  void addForce(const sf::Vector2f &force);

  // TODO: Should be handled event based?.
  void notifyGrounded();

  void multiplyVelocity(const sf::Vector2f &vector);

  sf::Vector2f getVelocity() const;

protected:
  bool grounded;
  sf::Vector2f velocity;
  float speed = 800.f;
  float friction = 9.5f;
  sf::Vector2f acceleration;
};
