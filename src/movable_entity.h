#pragma once

#include "entity.h"

class MovableEntity : public Entity {
public:
	MovableEntity(const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~MovableEntity() = default;
	void multiplyVelocity(const sf::Vector2f& vector);
	void update(const float& deltaTime) override;
	void addForce(const sf::Vector2f& force);

	sf::Vector2f getVelocity() const;
protected:
	sf::Vector2f velocity;
	float speed = 1600.f;
	float friction = 6.f;
	float maxSpeed = 500.f;
};
