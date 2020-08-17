#include "movable_entity.h"
#include <iostream>

MovableEntity::MovableEntity(const sf::Vector2f& position, const sf::Vector2f& velocity, const bool collidable,
                             const Sprite& sprite,
                             RestrictedQueue<Event*> eventQueue) :
        velocity{velocity}
        , Entity(position, collidable, sprite, eventQueue) {
}

MovableEntity::~MovableEntity() = default;

void MovableEntity::update(const float& deltaTime) {
    position += (speed * velocity) * deltaTime;
    sprite.update(deltaTime);
    setPosition(position);
}

void MovableEntity::render(sf::RenderTarget* renderTarget) {
    sprite.render(renderTarget);
}

void MovableEntity::multiplyVelocity(const sf::Vector2f& vector) {
    velocity.x *= vector.x;
    velocity.y *= vector.y;
}

void MovableEntity::addForce(const sf::Vector2f& force) {
    velocity += force;
}

sf::Vector2f MovableEntity::getVelocity() const {
    return velocity;
}

void MovableEntity::notifyGrounded() {
    grounded = true;
}

