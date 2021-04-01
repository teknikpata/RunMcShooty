#pragma once

#include "sprite.h"
#include <memory>
#include <unordered_map>


enum class AnimationState{
    IDLE,
    WALKING_DOWN,
    WALKING_UP,
    WALKING_LEFT,
    WALKING_RIGHT
};

class Animator{
public:
    explicit Animator(const Sprite& sprite) :
        currentState {AnimationState::IDLE}{
        animationMap.emplace(AnimationState::IDLE, std::make_shared<Sprite>(sprite));
    }
    ~Animator() = default;

    void update(const float deltaTime) {
        animationMap[currentState]->update(deltaTime);
    }

    void render(sf::RenderTarget* renderTarget){
        animationMap[currentState]->render(renderTarget);
    }

    void setPosition(const sf::Vector2f& position){
        animationMap[currentState]->setPosition(position);
    }

    void move(sf::Vector2f offset){
        animationMap[currentState]->move(offset);
    }


private:
    AnimationState currentState;
    std::unordered_map<AnimationState, std::shared_ptr<Sprite>> animationMap;
};