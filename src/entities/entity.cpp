#include "entity.h"

Entity::Entity(const sf::Vector2f& position, const bool collidable, const Sprite& sprite) :
    position(position),
    collidable(collidable),
    sprite(sprite),
    box(position, sprite.getSize()){
   this->sprite.setPosition(position);
}

Entity::~Entity() = default;

sf::Vector2f Entity::getPosition() const {
    return position;
}

void Entity::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
    sprite.setPosition(position);
    box.setPosition(position);
}

bool Entity::isCollidable() const {
    return collidable;
}

void Entity::setCollidable(const bool newCollidable) {
    collidable = newCollidable;
}

void Entity::move(const sf::Vector2f& offset) {
    position += offset;
    sprite.setPosition(position);
    box.setPosition(position);
}

const CollisionBox& Entity::getBounds() const {
    return box;
}

sf::Vector2f Entity::getSize() const {
    return box.getSize();
}