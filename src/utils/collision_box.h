#pragma once

#include <SFML/System/Vector2.hpp>


class CollisionBox {
public:
    enum class Constraints {
        VERTICAL,
        HORIZONTAL,
        NONE
    };

    CollisionBox(const sf::Vector2f& position, const sf::Vector2f& size,
                 Constraints collisionCheck = Constraints::NONE);

    ~CollisionBox();

    bool intersects(CollisionBox& other) const;

    bool contains(sf::Vector2f& point);

    void render(sf::RenderTarget* target);

    void setPosition(const sf::Vector2f& newPosition);

    void move(const sf::Vector2f& offset);

    sf::Vector2f getPosition() const;

    sf::Vector2f getCenter() const;

    sf::Vector2f getSize() const;

    float getWidth() const;

    float getHeight() const;

    float getRight() const;

    float getLeft() const;

    float getTop() const;

    float getBottom() const;

    sf::Vector2f getTopLeft() const;

    sf::Vector2f getTopRight() const;

    sf::Vector2f getBottomLeft() const;

    sf::Vector2f getBottomRight() const;

    Constraints getConstraints() const;

private:
    Constraints constraints;
    sf::Vector2f position;
    sf::Vector2f size;
};
