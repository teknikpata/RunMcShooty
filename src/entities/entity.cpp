#include "entity.h"

Entity::Entity(const sf::Vector2f& position, const std::string& filePath) :
    sprite(filePath),
    box(position, sprite.getSize()){
    sprite.setPosition(position);
}

Entity::Entity(const sf::Vector2f& position, const std::string& filePath, const unsigned int cellsX, const unsigned int cellsY, const float& timePerCell) :
    sprite(filePath, cellsX, cellsY, timePerCell),
    box(position, sprite.getSize()){

}

void Entity::render(sf::RenderTarget* renderTarget) {
    sprite.render(renderTarget);
    box.render(renderTarget);
}

void Entity::update(const float& deltaTime) {
    sprite.update(deltaTime);
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}

void Entity::setPosition(const sf::Vector2f& newPosition) {
    sprite.setPosition(newPosition);
    box.setPosition(newPosition);
}

void Entity::move(const sf::Vector2f& offset) {
    sprite.move(offset);
    box.move(offset);
}

const CollisionBox& Entity::getBounds() const {
    return box;
}

sf::Vector2f Entity::getSize() const {
    return box.getSize();
}


