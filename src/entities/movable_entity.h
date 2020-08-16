#pragma once

#include "entity.h"

class MovableEntity : public Entity {
public:
    MovableEntity(const sf::Vector2f &position, const sf::Vector2f &velocity, bool collidable, const Sprite &sprite,
                  RestrictedQueue<Event *>
                  eventQueue);

    ~MovableEntity() override;

    virtual void update(const float &deltaTime);

    virtual void render(sf::RenderTarget *renderTarget);

    void addForce(const sf::Vector2f &force);

    // TODO: Should be handled event based?.
    void notifyGrounded();

    void multiplyVelocity(const sf::Vector2f &vector);

    // --------------------------------------
    sf::Vector2f getVelocity() const;

protected:
    bool grounded;
    sf::Vector2f velocity;
    float speed = 2200.f;
    float friction = 9.5f;
    sf::Vector2f acceleration;
};
