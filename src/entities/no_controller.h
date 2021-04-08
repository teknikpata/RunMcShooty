#pragma once

#include "controller.h"

class NoController : public Controller {
 public:
  NoController() : Controller{} {}
  ~NoController() = default;

  sf::Vector2f getInput(const float &deltaTime) override {
    return {0.f, 0.f};
  }
};