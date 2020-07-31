#pragma once

#include <SFML/System/Vector2.hpp>
#include <math.h>

//TODO: Use namespace instead of class.
class Math {
public:
    static float vectorLength(const sf::Vector2f& v) {
        return sqrtf(v.x * v.x + v.y * v.y);
    }

    static sf::Vector2f normalizeVector(const sf::Vector2f& v) {
        const auto length = vectorLength(v);
        if (length != 0)
            return {v.x / length, v.y / length};

        return {0, 0};
    }
private:
    Math() = default;
    ~Math() = default;
};
