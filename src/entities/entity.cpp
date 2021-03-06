#include "entity.h"

Entity::Entity(const sf::Vector2f &position, const bool collidable,
               const Animator &animator, RestrictedQueue<Event *> eventQueue)
    : position{position}, collidable{collidable}, animator{animator},
      eventQueue{eventQueue} {
  this->animator.setPosition(position);
  box = CollisionBox{position, this->animator.getSize()};
}

Entity::~Entity() = default;

sf::Vector2f Entity::getPosition() const { return position; }

void Entity::setPosition(const sf::Vector2f &newPosition) {
  position = newPosition;
  animator.setPosition(position);
  box.setPosition(position);
}

bool Entity::isCollidable() const { return collidable; }

void Entity::setCollidable(const bool newCollidable) {
  collidable = newCollidable;
}

void Entity::move(const sf::Vector2f &offset) {
  position += offset;
  animator.setPosition(position);
  box.setPosition(position);
}

const CollisionBox &Entity::getBounds() const { return box; }

sf::Vector2f Entity::getSize() const { return box.getSize(); }

sf::Vector2f Entity::getCenter() const {
  return {position.x + (box.getSize().x / 2),
          position.y + (box.getSize().y / 2)};
}
