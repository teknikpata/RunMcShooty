#pragma once

#include <unordered_map>
#include "graphic/sprite.h"

enum struct AnimationState{
    IDLE,
    WALKING_DOWN,
    WALKING_UP,
    WALKING_LEFT,
    WALKING_RIGHT
};

class AnimationController{
public:
    AnimationController() = default;
    void addState(AnimationState animationState, Sprite sprite) {
        spriteMap.emplace(animationState, sprite);
    }
    void update(const float deltaTime) {
        spriteMap[currentState].update(deltaTime);
    }
    void render(sf::RenderTarget& target){
        spriteMap[currentState].render(target);
    }

    void setState(const AnimationState state){
        currentState = state;
    }
private:
    AnimationState currentState;
    std::unordered_map<AnimationState, Sprite> spriteMap;

};