#include "Entitiy.h"

Entity::Entity(const sf::Vector2f& position,
               const Type type,
               ResourceManager<sf::Texture, Resources::Textures>& textureManager) :
               type{type},
               textureManager{textureManager} {
    switch (type) {
        case Type::Player:
            sprite.setTexture(textureManager.get(Resources::Textures::Player));
            break;
        case Type::Platform:
            sprite.setTexture(textureManager.get(Resources::Textures::Platform));
            break;
        case Type::Pillar:
            sprite.setTexture(textureManager.get(Resources::Textures::Pillar));
            break;
    }
    const auto bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
    setPosition(position);
}

Entity::~Entity() = default;

void Entity::setVelocity(const sf::Vector2f& newVelocity) {
    velocity = newVelocity;
}

void Entity::setVelocity(const float newX, const float newY) {
    velocity = {newX, newY};
}

sf::Vector2f Entity::getVelocity() const {
    return velocity;
}

void Entity::accelerate(const sf::Vector2f& force) {
    velocity += force;
}

void Entity::accelerate(const float forceX, const float forceY) {
    velocity += {forceX, forceY};
}

void Entity::updateThis(const float& deltaTime) {
    move(velocity * deltaTime);
}

void Entity::drawThis(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

