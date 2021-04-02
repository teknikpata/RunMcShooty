#pragma once

#include "animator.h"
#include "entities/sprite.h"
#include "events/event.h"
#include "utils/collision_box.h"
#include "utils/restricted_queue.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

class Entity {
public:
  Entity(const sf::Vector2f &position, bool collidable, const Animator
                                                            &animator,
         RestrictedQueue<Event *> eventQueue);

  virtual ~Entity();

  virtual void update(const float &deltaTime) = 0;
  virtual void render(sf::RenderTarget *renderTarget) = 0;

  sf::Vector2f getPosition() const;

  sf::Vector2f getCenter() const;

  void setPosition(const sf::Vector2f &newPosition);

  bool isCollidable() const;

  void setCollidable(bool newCollidable);

  void move(const sf::Vector2f &offset);

  const CollisionBox &getBounds() const;

  sf::Vector2f getSize() const;

  // TODO: move into MovableEntity class
  sf::Vector2f getVelocity();

protected:
  sf::Vector2f position;
  bool collidable;
  CollisionBox box;
  Animator animator;

  RestrictedQueue<Event *> eventQueue;
};