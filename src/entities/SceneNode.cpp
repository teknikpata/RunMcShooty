#include <iostream>
#include <cassert>
#include "SceneNode.h"


SceneNode::SceneNode() :
    parent{nullptr} {
}

SceneNode::~SceneNode() = default;

void SceneNode::addChild(std::unique_ptr<SceneNode> node) {
    children.size();
    std::cout << node->getPosition().x << std::endl;
    node->parent = this;
    children.push_back(std::move(node));
}

std::unique_ptr<SceneNode> SceneNode::removeChild(const SceneNode& node) {
    auto found = std::find_if(std::begin(children), std::end(children) ,[&](std::unique_ptr<SceneNode>& child) {
        return child.get() == &node;
    });
    assert(found != std::end(children));
    auto child = std::move(*found);
    child->parent = nullptr;
    children.erase(found);
    return child;
}

void SceneNode::update(const float& deltaTime) {
    updateThis(deltaTime);
    for(const auto& child : children)
        child->update(deltaTime);
}

void SceneNode::updateThis(const float& deltaTime) {}

void SceneNode::drawThis(sf::RenderTarget& target, sf::RenderStates states) const {}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawThis(target, states);
    for(const auto& child : children)
        child->draw(target, states);
}

sf::Transform SceneNode::getWorldTransform() const {
    auto transform = sf::Transform::Identity;
    auto node = this;
    while(node != nullptr){
        transform *= node->getTransform();
        node = node->parent;
     }
}

sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f{};
}
