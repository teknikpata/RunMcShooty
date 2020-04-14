#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <math.h>
#include "entities/entity.h"

class Camera {
public:
    Camera(const sf::Vector2f position, sf::Vector2i bounds) :
            bounds{bounds} {
        view.reset(sf::FloatRect(position.x, position.y, bounds.x, bounds.y));
    }

    ~Camera() = default;

    sf::View operator()() {
        if (target) {
            const auto& targetCenter = target->getCenter();
            const auto& viewCenter = view.getCenter();

            auto vector = targetCenter - viewCenter;
            float deltaX = 0.f;
            float deltaY = 0.f;

            if(fabs(vector.x) > trackingArea.x / 2){
                if(vector.x > 0.f){
                    deltaX = targetCenter.x - (viewCenter.x + (trackingArea.x / 2));
                }
                else {
                    deltaX = targetCenter.x - (viewCenter.x - (trackingArea.x / 2));
                }
            }
            if(fabs(vector.y) > trackingArea.y / 2){
                if(vector.y > 0.f){
                    deltaY = targetCenter.y - (viewCenter.y + (trackingArea.y / 2));
                }
                else {
                    deltaY = targetCenter.y - (viewCenter.y - (trackingArea.y / 2));
                }
            }
            view.move(deltaX, deltaY);
        }
        return view;
    }

    void move(const sf::Vector2f &offset) {
        view.move(offset);
    }

    void rotate(float angle) {
        view.rotate(angle);
    }

    void lookAt(const sf::Vector2f &point) {
        view.setCenter(point);
    }

    void follow(std::shared_ptr<Entity> target, const sf::Vector2f &searchArea) {
        this->trackingArea = searchArea;
        this->target = target;
    }

private:
    sf::View view;
    sf::Vector2i bounds;
    std::shared_ptr<Entity> target;
    // Need a new name
    sf::Vector2f trackingArea;
};