#pragma once

#include "entity.h"

class StaticEntity : public Entity {
public:
    StaticEntity(const sf::Vector2f& position, bool collidable, const Sprite& sprite, RestrictedQueue<Event*>
    eventQueue);
    ~StaticEntity() override;

    void render(sf::RenderTarget* renderTarget) override;
    void update(const float& deltaTime) override;
};

