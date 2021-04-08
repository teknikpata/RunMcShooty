#include "sprite.h"

Sprite::Sprite(std::shared_ptr<sf::Texture> texture, const unsigned int cellsX,
               const unsigned int cellsY, const float &timePerCell)
    : texture(texture), timePerCell(timePerCell), animated(true) {
  elapsedTime = 0;
  spriteSheetSize = texture->getSize();
  currentPosition = {0, 0};
  cellSize = {static_cast<int>(spriteSheetSize.x / cellsX),
              static_cast<int>(spriteSheetSize.y / cellsY)};
  sprite.setTexture(*texture);
  sprite.setTextureRect(
      {currentPosition.x, currentPosition.y, cellSize.x, cellSize.y});
}

Sprite::Sprite(std::shared_ptr<sf::Texture> texture)
    : texture(texture), animated(false) {
  elapsedTime = 0;
  spriteSheetSize = texture->getSize();
  currentPosition = {0, 0};
  cellSize = {static_cast<int>(spriteSheetSize.x),
              static_cast<int>(spriteSheetSize.y)};
  sprite.setTexture(*texture);
  sprite.setTextureRect(
      {currentPosition.x, currentPosition.y, cellSize.x, cellSize.y});
}

Sprite::~Sprite() = default;

void Sprite::update(const float &deltaTime) {
  if (!animated)
    return;

  elapsedTime += deltaTime;
  if (elapsedTime < timePerCell)
    return;

  elapsedTime = 0;

  if (currentPosition.x + cellSize.x >= spriteSheetSize.x) {
    currentPosition.x = 0;
    if (currentPosition.y + cellSize.y >= spriteSheetSize.y)
      currentPosition.y = 0;
    else
      currentPosition.y += cellSize.y;
  } else {
    currentPosition.x += cellSize.x;
  }
  sprite.setTextureRect(
      {currentPosition.x, currentPosition.y, cellSize.x, cellSize.y});
}

void Sprite::render(sf::RenderTarget *renderTarget) {
  renderTarget->draw(sprite);
}

void Sprite::setPosition(const sf::Vector2f &position) {
  sprite.setPosition(position);
}

void Sprite::move(const sf::Vector2f &offset) { sprite.move(offset); }

sf::Vector2f Sprite::getPosition() const { return sprite.getPosition(); }

sf::Vector2f Sprite::getSize() const {
  return {static_cast<float>(cellSize.x), static_cast<float>(cellSize.y)};
}