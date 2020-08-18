#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace math {
    template<class T>
    float vectorLength(const sf::Vector2<T>& v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    template<class T>
    sf::Vector2f normalizeVector(const sf::Vector2<T>& v) {
        const auto length = vectorLength(v);
        if (length != 0) {
            return {v.x / length, v.y / length};
        }

        return {0, 0};
    }
} // namespace math
