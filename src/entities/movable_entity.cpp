#include "movable_entity.h"
#include <SFML/Window/Keyboard.hpp>
#include "utils/math.h"

MovableEntity::MovableEntity(const sf::Vector2f& position, const bool collidable, const Sprite& sprite) :
    Entity(position, collidable, sprite) {
}

MovableEntity::~MovableEntity() = default;

void MovableEntity::update(const float& deltaTime) {
    sf::Vector2f acceleration;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        acceleration += sf::Vector2f(-1, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        acceleration += sf::Vector2f(1, 0);
    }
    acceleration *= speed;
    acceleration += -velocity * friction;
    position += (acceleration * 0.5f * (deltaTime * deltaTime)) + (velocity * deltaTime);
    velocity += acceleration * deltaTime;
    //TODO: Dont let entities handle gravity.
    addForce(sf::Vector2f(0, 50.f));
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
