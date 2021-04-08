#pragma once

#include "controller.h"

class TrajectoryController : public Controller {
 public:
  explicit TrajectoryController(const sf::Vector2f &direction) : direction{direction} {}
  ~TrajectoryController() = default;
  sf::Vector2f getInput(const float &deltaTime) override {
    return direction;
  }

 private:
  sf::Vector2f direction;
};