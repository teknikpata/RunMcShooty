#include "game.h"
#include "entities/random_controller.h"
#include "entities/trajectory_controller.h"
#include "utils/math.h"
#include <memory>

const auto TimePerFrame = sf::seconds(1.0f / 60.f);
constexpr int HEIGHT = 800;
constexpr int WIDTH = 1200;

Game::Game() : camera{}, world{"1"} {
  window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "RunMcShooty");

  textureManager.load("player", "assets/graphics/player.png");
  textureManager.load("character_idle", "assets/graphics/character_front.png");
  textureManager.load("character_front", "assets/graphics/walking_forward.png");
  textureManager.load("character_left", "assets/graphics/walking_left.png");
  textureManager.load("character_right", "assets/graphics/walking_right.png");
  textureManager.load("platform", "assets/graphics/platform.png");
  textureManager.load("pillar", "assets/graphics/pillar.png");
  textureManager.load("projectile", "assets/graphics/projectile.png");
  textureManager.load("enemy", "assets/graphics/enemy.png");

  auto playerAnimator = Animator{Sprite{textureManager.get("character_front"), 4, 1, 1.f}};
  playerAnimator.addAnimation(Sprite{textureManager.get("character_front"), 4, 1, .15f},
                              AnimationState::WALKING_DOWN);
  playerAnimator.addAnimation(textureManager.get("character_left"),
                              AnimationState::WALKING_LEFT);
  playerAnimator.addAnimation(textureManager.get("character_right"),
                              AnimationState::WALKING_RIGHT);

  world.addPlayer(Player{sf::Vector2f{200, 225}, 2200.f, true, playerAnimator,
                         RestrictedQueue<Event *>{eventQueue}});
  camera.follow(world.getPlayer(), {300, 200});
  world.addEntity(StaticEntity{sf::Vector2f{200, 265}, true,
                               Animator{textureManager.get("platform")},
                               RestrictedQueue<Event *>{eventQueue}});
  world.addEntity(StaticEntity{sf::Vector2f{0, 400}, true,
                               Animator{textureManager.get("platform")},
                               RestrictedQueue<Event *>{eventQueue}});
  world.addEntity(StaticEntity{sf::Vector2f{401, 400}, true,
                               Animator{textureManager.get("platform")},
                               RestrictedQueue<Event *>{eventQueue}});
  world.addEntity(StaticEntity{sf::Vector2f{0, 400}, true,
                               Animator{textureManager.get("platform")},
                               RestrictedQueue<Event *>{eventQueue}});
  world.addEntity(StaticEntity{sf::Vector2f{400, 275}, false,
                               Animator{textureManager.get("pillar")},
                               RestrictedQueue<Event *>{eventQueue}});

  world.addEntity(MovableEntity{sf::Vector2f{-200, 300}, std::make_shared<RandomController>(3.5f), 75.f, true,
                                Animator{textureManager.get("enemy")},
                                RestrictedQueue<Event *>{eventQueue}});
  world.addEntity(MovableEntity{sf::Vector2f{-400, 400}, std::make_shared<RandomController>(1.5f), 100.f, true,
                                Animator{textureManager.get("enemy")},
                                RestrictedQueue<Event *>{eventQueue}});
  world.addEntity(MovableEntity{sf::Vector2f{-100, 200}, std::make_shared<RandomController>(2.f), 50.f, true,
                                Animator{textureManager.get("enemy")},
                                RestrictedQueue<Event *>{eventQueue}});
  world.addEntity(MovableEntity{sf::Vector2f{-200, 100}, std::make_shared<RandomController>(4.f), 25.f, true,
                                Animator{textureManager.get("enemy")},
                                RestrictedQueue<Event *>{eventQueue}});
}

Game::~Game() { delete window; }

void Game::run() {
  sf::Clock clock;
  auto lastUpdate = sf::Time::Zero;
  while (window->isOpen()) {
    lastUpdate += clock.restart();
    while (lastUpdate > TimePerFrame) {
      lastUpdate -= TimePerFrame;
      sf::Event event;
      while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
          window->close();
      }

      while (!eventQueue.empty()) {
        auto *myEvent = eventQueue.front();
        switch (myEvent->type) {
          case Event::Type::Attack: {
            auto attackEvent = dynamic_cast<AttackEvent *>(myEvent);
            auto direction =
                window->mapPixelToCoords(sf::Mouse::getPosition(*window)) - attackEvent->position;
            direction = math::normalizeVector(direction);
            world.addEntity(
                MovableEntity{attackEvent->position, std::make_shared<TrajectoryController>(direction), 800.f, false,
                              Animator{textureManager.get("projectile")},
                              RestrictedQueue<Event *>{eventQueue}});
            break;
          }
          case Event::Type::Input: {
            break;
          }
          case Event::Type::Move: {
            break;
          }
          default: {
            break;
          }
        }
        eventQueue.pop();
      }
      update(TimePerFrame.asSeconds());
    }
    render();
  }
}

void Game::resolve(const Collisions &collisions) {
  for (const auto &collision : collisions) {
    auto e1Bounds = collision.e1->getBounds();
    auto e2Bounds = collision.e2->getBounds();

    // Check if collision is already solved
    if (!e1Bounds.intersects(e2Bounds))
      continue;

    auto movEntity = collision.e1;
    movEntity->move(collision.depth);
    switch (collision.side) {
      case CollisionData::Side::TOP:
        movEntity->multiplyVelocity(sf::Vector2f(1.f, 0.f));
        break;
      case CollisionData::Side::BOTTOM:
        movEntity->multiplyVelocity(sf::Vector2f(1.f, 0.f));
        movEntity->notifyGrounded();
        break;
      case CollisionData::Side::LEFT:
        movEntity->multiplyVelocity(sf::Vector2f(0.f, 1.f));
        break;
      case CollisionData::Side::RIGHT:
        movEntity->multiplyVelocity(sf::Vector2f(0.f, 1.f));
        break;
      case CollisionData::Side::NONE:
        break;
    }
  }
}

void Game::update(const float &deltaTime) {
  world.update(deltaTime);
  resolve(world.getCollisions());
  window->setView(camera(window->getView()));
  render();
}

void Game::render() {
  window->clear();
  world.render(window);
  window->display();
}