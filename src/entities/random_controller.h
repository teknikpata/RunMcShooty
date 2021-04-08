#pragma once

#include "controller.h"
#include "utils/timer.h"

namespace {
float getRandomValue() {
  return rand() % 2 == 0 ? rand() % 2 : -rand() % 2;
}
}// namespace

class RandomController : public Controller {
 public:
  explicit RandomController(const float &timeToChangeDirection) : directionChangeTimer{timeToChangeDirection, "DirectionChangeTimer"}, direction{sf::Vector2f{getRandomValue(), getRandomValue()}} {}
  ~RandomController() = default;
  sf::Vector2f getInput(const float &deltaTime) override {
    directionChangeTimer.update(deltaTime);
    if (directionChangeTimer.done()) {
      direction = sf::Vector2f{getRandomValue(), getRandomValue()};
      directionChangeTimer.reset();
    }
    return direction;
  }

 private:
  Timer directionChangeTimer;
  sf::Vector2f direction;
};