#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "entities/entity.h"

namespace {
    sf::RectangleShape createRectangle(const sf::Vector2f &position, const sf::Vector2f &size, sf::Color color) {
        sf::RectangleShape rectangle;
        rectangle.setSize(size);
        rectangle.setFillColor(color);
        rectangle.setOutlineColor(color);
        rectangle.setOutlineThickness(5.f);
        rectangle.setPosition(position);
        return rectangle;
    };
}
class Camera {
public:
    Camera() = default;

    ~Camera() = default;

    sf::View operator()(const sf::View &currentView) {
        auto newView = currentView;
        if (target) {
            const auto &targetCenter = target->getCenter();
            const auto &viewCenter = newView.getCenter();

            const auto &displacement = targetCenter - viewCenter;
            float deltaX = 0.f;
            float deltaY = 0.f;

            if (fabs(displacement.x) > trackingArea.x / 2) {
                if (displacement.x > 0.f)
                    deltaX = targetCenter.x - (viewCenter.x + (trackingArea.x / 2));
                else
                    deltaX = targetCenter.x - (viewCenter.x - (trackingArea.x / 2));
            }

            if (fabs(displacement.y) > trackingArea.y / 2) {
                if (displacement.y > 0.f)
                    deltaY = targetCenter.y - (viewCenter.y + (trackingArea.y / 2));
                else
                    deltaY = targetCenter.y - (viewCenter.y - (trackingArea.y / 2));
            }
            newView.move(sf::Vector2f{deltaX, deltaY});
        }
        return newView;
    }

    void move(const sf::Vector2f &offset) {
        // view.move(offset);
    }

    void rotate(float angle) {
        // view.rotate(angle);
    }

    void lookAt(const sf::Vector2f &point) {
        // view.setCenter(point);
    }

    void follow(std::shared_ptr<Entity> target, const sf::Vector2f &searchArea) {
        this->trackingArea = searchArea;
        this->target = target;
        // view.setCenter(target->getCenter());
    }

private:
    std::shared_ptr<Entity> target;
    sf::Vector2f trackingArea;
};