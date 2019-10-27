#pragma once

#include "entity.h"
#include "entities/sprite.h"

class MovableEntity : public Entity {
public:
	MovableEntity(const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~MovableEntity() = default;
	void multiplyVelocity(const sf::Vector2f& vector);
	void update(const float& deltaTime) override;
	void render(sf::RenderTarget* renderTarget) override;
	void addForce(const sf::Vector2f& force);
	void jump();
	void IsGrounded();

	sf::Vector2f getVelocity() const;
protected:
    bool isGrounded;
    int jumpCharges;
    int maxJumpCharges = 1;
	sf::Vector2f velocity;
	float speed = 1600.f;
	float friction = 6.f;
	float maxSpeed = 500.f;
};
