#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "collision_box.h"

class Entity
{
public:
	Entity(const sf::Vector2f& position, const sf::Vector2f& size);
	virtual ~Entity() = default;
	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* renderTarget);
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& newPosition);
    void move(const sf::Vector2f& offset);
	const CollisionBox& getBounds() const;
	sf::Vector2f getSize() const;

    sf::Vector2f getVelocity();

protected:
	sf::RectangleShape shape;
	CollisionBox box;
};
