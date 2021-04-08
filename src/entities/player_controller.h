#pragma once

#include "controller.h"

class PlayerController : public Controller {
 public:
  PlayerController() : Controller{} {}
  ~PlayerController() = default;
  sf::Vector2f getInput(const float &deltaTime) override {
    sf::Vector2f input = {};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
      input += sf::Vector2f(-1, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
      input += sf::Vector2f(1, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
      input += sf::Vector2f(0, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
      input += sf::Vector2f(0, -1);
    }
    return input;
  }
};