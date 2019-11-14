#include "static_entity.h"

StaticEntity::StaticEntity(const sf::Vector2f& position, const bool collidable, const Sprite& sprite) :
    Entity{position, collidable, sprite} {}

StaticEntity::~StaticEntity() = default;

void StaticEntity::update(const float& deltaTime) {

}
void StaticEntity::render(sf::RenderTarget* renderTarget) {
    sprite.render(renderTarget);
}
