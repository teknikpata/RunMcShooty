#include "texture_manager.h"

TextureManager::TextureManager() = default;

TextureManager::~TextureManager() = default;

bool TextureManager::load(const std::string& id, const std::string& filePath) {
    sf::Texture texture;
    texture.loadFromFile(filePath);
    textures.insert(std::make_pair(id, std::make_shared<sf::Texture>(texture)));
    return true;
}
std::shared_ptr<sf::Texture> TextureManager::get(const std::string& id) {
    return textures.at(id);
}

