#pragma once

#include "events/event.h"
#include "managers/texture_manager.h"
#include "utils/camera.h"
#include "world.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include <queue>

class Game {
 public:
  Game();

  ~Game();

  void run();

 private:
  void update(const float &deltaTime);

  void render();

  void resolve(const Collisions &collisions);

  World world;
  Camera camera;
  sf::RenderWindow *window;
  TextureManager textureManager;

  std::queue<Event *> eventQueue;
};