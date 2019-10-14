#include "collision_box.h"

CollisionBox::CollisionBox(const sf::Vector2f& position, const sf::Vector2f& size, const Constraints constraints) :
	position{ position },
	size{ size },
	constraints{ constraints } {
}

CollisionBox::~CollisionBox() {}

bool CollisionBox::contains(sf::Vector2f& point) {
	return position.x  < point.x  &&
		position.x + size.x > point.x &&
		position.y  < point.y &&
		position.y + size.y > position.y;
}

void CollisionBox::setPosition(const sf::Vector2f& newPosition) {
	position = newPosition;
}

void CollisionBox::move(const sf::Vector2f& offset) {
	position += offset;
}

bool CollisionBox::intersects(CollisionBox& other) const {
	return position.x  < other.position.x + other.size.x &&
		position.x + size.x > other.position.x &&
		position.y  < other.position.y + other.size.y &&
		position.y + size.y > other.position.y;
}

sf::Vector2f CollisionBox::getPosition() const {
	return position;
}

sf::Vector2f CollisionBox::getSize() const {
	return size;
}

float CollisionBox::getHeight() const {
	return size.y;
}

float CollisionBox::getWidth() const {
	return size.x;
}

float CollisionBox::getRight() const {
	return position.x + size.x;
}


float CollisionBox::getLeft() const {
	return position.x;
}


float CollisionBox::getTop() const {
	return position.y;
}


float CollisionBox::getBottom() const {
	return position.y + size.y;
}

sf::Vector2f CollisionBox::getMiddlePoint() const {
	return{ position.x + size.x / 2, position.y + size.y / 2 };
}

sf::Vector2f CollisionBox::getBottomLeft() const {
	return{ position.x, position.y + size.y };
}

sf::Vector2f CollisionBox::getBottomRight() const {
	return{ position.x + size.x, position.y + size.y };
}

sf::Vector2f CollisionBox::getTopLeft() const {
	return{ position.x, position.y };
}

sf::Vector2f CollisionBox::getTopRight() const {
	return{ position.x + size.x, position.y };
}

CollisionBox::Constraints CollisionBox::getConstraints() const {
	return constraints;
};






