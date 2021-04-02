#include "static_entity.h"

StaticEntity::StaticEntity(const sf::Vector2f &position, const bool collidable,
                           const Animator &animator,
                           RestrictedQueue<Event *> eventQueue)
    : Entity{position, collidable, animator, eventQueue} {}

StaticEntity::~StaticEntity() = default;

void StaticEntity::update(const float &deltaTime) {}

void StaticEntity::render(sf::RenderTarget *renderTarget) {
  animator.render(renderTarget);
}
