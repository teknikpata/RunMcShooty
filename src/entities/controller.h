#pragma once

#include <SFML/System/Vector2.hpp>

class Controller {
 public:
  Controller() = default;
  ~Controller() = default;
  virtual sf::Vector2f getInput(const float &deltaTime) = 0;
};
