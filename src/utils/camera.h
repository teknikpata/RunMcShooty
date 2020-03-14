#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include "entities/entity.h"

class Camera {
public:
    Camera(const sf::Vector2f position, sf::Vector2i bounds) :
        bounds{bounds}{
        view.reset(sf::FloatRect(position.x, position.y, bounds.x, bounds.y));
    }
    ~Camera() = default;

    sf::View operator()(){
        if(target){
            auto targetPosition = target->getPosition();
            const auto& targetBounds = target->getSize();

            targetPosition.x += targetBounds.x / 2;
            targetPosition.y += targetBounds.y / 2;
            targetPosition.x -= bounds.x / 2;
            targetPosition.y -= bounds.y / 2;
            view.reset(sf::FloatRect(targetPosition.x, targetPosition.y, bounds.x, bounds.y));
        }
        return view;
    }

    void move(const sf::Vector2f& offset) {
        view.move(offset);
    }
    void rotate(float angle) {
        view.rotate(angle);
    }

    void lookAt(const sf::Vector2f& point) {
        view.setCenter(point);
    }

    void follow(std::shared_ptr<Entity> target) {
        this->target = target;
    }

private:
    sf::View view;
    sf::Vector2i bounds;
    std::shared_ptr<Entity> target;
    // Need a new name
    sf::Vector2f focusBounds;
};