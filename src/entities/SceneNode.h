#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
    SceneNode();
    ~SceneNode();

    void addChild(std::unique_ptr<SceneNode> node);
    std::unique_ptr<SceneNode> removeChild(const SceneNode& node);

    void update(const float& deltaTime);
protected:
    virtual void updateThis(const float& deltaTime);
    virtual void drawThis(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
    SceneNode* parent;
    std::vector<std::unique_ptr<SceneNode>> children;
};
