#include "game.h"

const auto TimePerFrame = sf::seconds(1.0f / 60.f);
constexpr int HEIGHT = 800;
constexpr int WIDTH = 1200;

Game::Game() :
        camera{}
        , world{"1"} {
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "RunMcShooty");

    textureManager.load("player", "assets/graphics/player.png");
    textureManager.load("platform", "assets/graphics/platform.png");
    textureManager.load("pillar", "assets/graphics/pillar.png");

    Sprite playerSprite{textureManager.get("player"), 2, 2, 1.f};
    Sprite platformSprite{textureManager.get("platform")};
    Sprite pillarSprite{textureManager.get("pillar")};

    world.addPlayer(Player{sf::Vector2f(200, 225), true, playerSprite, RestrictedQueue<Event *>{eventQueue}});
    camera.follow(world.getPlayer(), {300, 200});

    world.addEntity(StaticEntity{sf::Vector2f{200, 265}, true, platformSprite, RestrictedQueue<Event *>{eventQueue}});
    world.addEntity(StaticEntity{sf::Vector2f{0, 400}, true, platformSprite, RestrictedQueue<Event *>{eventQueue}});
    world.addEntity(StaticEntity{sf::Vector2f{401, 400}, true, platformSprite, RestrictedQueue<Event *>{eventQueue}});
    world.addEntity(StaticEntity{sf::Vector2f{0, 400}, true, platformSprite, RestrictedQueue<Event *>{eventQueue}});
    world.addEntity(StaticEntity{sf::Vector2f{400, 275}, false, pillarSprite, RestrictedQueue<Event *>{eventQueue}});
}

Game::~Game() {
    delete window;
}

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
                    case Event::Type::Attack:
                        auto attackEvent = static_cast<AttackEvent*>(myEvent);

                        auto direction = window->mapPixelToCoords(sf::Mouse::getPosition(*window)) - attackEvent->position;
                        float pX = powf(direction.x, 2);
                        float pY = powf(direction.y, 2);
                        auto length = sqrtf(pX + pY);
                        auto normalizedDirection = sf::Vector2f{0,0};
                        if (length != 0) {
                            normalizedDirection = sf::Vector2f{direction.x / length, direction.y / length};
                        }
                        std::cout << "Position: " << attackEvent->position.x << " : " << attackEvent->position.y << " MousePos: " << sf::Mouse::getPosition(*window).x << " : " << sf::Mouse::getPosition(*window).y <<  " Dir: " << normalizedDirection.x << " : " << normalizedDirection.y << std::endl;
                        world.addEntity(
                                MovableEntity{attackEvent->position, normalizedDirection, false, textureManager.get(
                                        "platform"), RestrictedQueue<Event *>{eventQueue}});
                        break;
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

        //Check if collision is already solved
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