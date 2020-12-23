#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "events/event.h"
#include "utils/collision_box.h"
#include "graphic/sprite.h"
#include "utils/restricted_queue.h"

class Entity {
public:
    Entity(const sf::Vector2f& position, bool collidable, const Sprite& sprite, RestrictedQueue<Event*> eventQueue);

    virtual ~Entity();

    virtual void update(const float& deltaTime) = 0;
    virtual void render(sf::RenderTarget* renderTarget) = 0;

    sf::Vector2f getPosition() const;

    sf::Vector2f getCenter() const;

    void setPosition(const sf::Vector2f& newPosition);

    bool isCollidable() const;

    void setCollidable(bool newCollidable);

    void move(const sf::Vector2f& offset);

    const CollisionBox& getBounds() const;

    sf::Vector2f getSize() const;

    //TODO: move into MovableEntity class
    sf::Vector2f getVelocity();

protected:
    sf::Vector2f position;
    bool collidable;
    Sprite sprite;
    CollisionBox box;

    RestrictedQueue<Event*> eventQueue;
};