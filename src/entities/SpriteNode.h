#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "entities/SceneNode.h"

class SpriteNode :  public SceneNode {
    sf::Sprite sprite;
public:
    explicit SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);
    ~SpriteNode() = default;
private:
    void drawThis(sf::RenderTarget& target, sf::RenderStates states) const override;
};