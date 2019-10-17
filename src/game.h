#pragma once
#include "entity.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "movable_entity.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	struct CollisionData {
		MovableEntity* e1;
		Entity* e2;
		sf::Vector2f depth;
		int distanceX;
		int distanceY;
		CollisionBox::Side side;
		CollisionData(MovableEntity* e1, Entity* e2, sf::Vector2f depth, const int distanceX, const int distanceY, CollisionBox::Side side) :
			e1(e1),
			e2(e2),
			depth(depth),
			distanceX(distanceX),
			distanceY(distanceY),
			side(side){ }
			
	};
	using Collisions = std::vector<CollisionData>;

	void update(const float& deltaTime);
	void render();
	Collisions getCollisions();

    void resolve(const Collisions& collisions);
	sf::RenderWindow* window;
	std::vector<Entity*> entities;
	std::vector<MovableEntity*> movables;
};