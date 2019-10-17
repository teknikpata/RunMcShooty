#include "movable_entity.h"
#include <SFML/Window/Keyboard.hpp>
#include "math.h"

MovableEntity::MovableEntity(const sf::Vector2f& position, const sf::Vector2f& size) :
	Entity(position, size) {
}

void MovableEntity::update(const float& deltaTime) {
	auto position = getPosition();
	sf::Vector2f acceleration;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		jump();
	}
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
	setPosition(position); 
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

void MovableEntity::IsGrounded() {
    isGrounded = true;
    jumpCharges = maxJumpCharges;
}

void MovableEntity::jump() {
    if(jumpCharges > 0){
        jumpCharges--;
        addForce(sf::Vector2f(0, -2000));
    }
}
