#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

class Sprite {
public:
    Sprite(std::shared_ptr<sf::Texture> texture, const unsigned int cellsX, const unsigned int cellsY,
           const float& timePerCell);

    Sprite(std::shared_ptr<sf::Texture> texture);

    ~Sprite();

    void update(const float& deltaTime);

    void render(sf::RenderTarget* renderTarget);

    void setPosition(const sf::Vector2f& vector2);

    void move(const sf::Vector2f& offset);

    sf::Vector2f getPosition() const;

    sf::Vector2f getSize() const;

private:
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    std::string filePath;
    sf::Vector2u spriteSheetSize;
    sf::Vector2i currentPosition;
    sf::Vector2i cellSize;
    float elapsedTime;
    float timePerCell;
    bool animated;
};
