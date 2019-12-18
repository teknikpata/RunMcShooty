#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "SceneNode.h"
#include "managers/ResourceManager.h"

class Entity : public SceneNode {
public:
    enum class Type{
        Player,
        Platform,
        Pillar,
    };
private:
    sf::Vector2f velocity;
    Type type;
    sf::Sprite sprite;
    const ResourceManager<sf::Texture, Resources::Textures>& textureManager;

public:
	Entity(const sf::Vector2f& position,
	       Type type,
	       ResourceManager<sf::Texture, Resources::Textures>& texutreManager);
	~Entity() override;
	void setVelocity(const sf::Vector2f& newVelocity);
	void setVelocity(float newX, float newY);
	sf::Vector2f getVelocity() const;
	void accelerate(const sf::Vector2f& force);
	void accelerate(float forceX, float forceY);
	void updateThis(const float& deltaTime) override;
    sf::FloatRect getBoundingRect() const override ;
protected:
    // SceneNode
    void drawThis(sf::RenderTarget& target, sf::RenderStates states) const override;
};