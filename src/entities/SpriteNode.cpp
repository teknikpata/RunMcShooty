#include "entities/SpriteNode.h"

SpriteNode::SpriteNode(const sf::Texture &texture) :
    sprite{texture} {}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect) :
    sprite{texture, rect} {}

void SpriteNode::drawThis(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

