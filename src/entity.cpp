#include "entity.h"

Entity::Entity(const sf::Vector2f& position, const sf::Vector2f& size) :
	box(CollisionBox(position, size)) {
	shape.setSize(size);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(0);
	shape.setPosition(position);
}

void Entity::render(sf::RenderTarget* renderTarget) {
	renderTarget->draw(shape);
}

void Entity::update(const float& deltaTime) {
}

sf::Vector2f Entity::getPosition() const {
	return shape.getPosition();
}
void Entity::setPosition(const sf::Vector2f&  newPosition) {
	shape.setPosition(newPosition);
	box.setPosition(newPosition);
}

void Entity::move(const sf::Vector2f&  offset) {
	shape.move(offset);
	box.move(offset);
}

const CollisionBox& Entity::getBounds() const {
	return box;
}

sf::Vector2f Entity::getSize() const {
	return shape.getSize();
}

