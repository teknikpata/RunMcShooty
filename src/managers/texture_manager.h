#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class TextureManager {
 public:
  TextureManager();

  ~TextureManager();

  bool load(const std::string &id, const std::string &filePath);

  std::shared_ptr<sf::Texture> get(const std::string &id);

 private:
  std::map<std::string, std::shared_ptr<sf::Texture>> textures;
};
