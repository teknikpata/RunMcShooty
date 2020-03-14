#pragma once

#include "entity.h"

class MovableEntity : public Entity {
public:
	MovableEntity(const sf::Vector2f& position, bool collidable, const Sprite& sprite);
	~MovableEntity() override;

	void update(const float& deltaTime) override;
	void render(sf::RenderTarget* renderTarget) override;

	void addForce(const sf::Vector2f& force);

	// TODO: Should be handled event based.
	void notifyGrounded();
    void multiplyVelocity(const sf::Vector2f& vector);
    // --------------------------------------
	sf::Vector2f getVelocity() const;
protected:
    bool grounded;
	sf::Vector2f velocity;
	float speed = 2200.f;
	float friction = 9.5f;
	//float maxSpeed = 2000.f;
};
