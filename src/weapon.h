#pragma once
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include "utils/timer.h"

class Weapon {
public:
    Weapon(int maxBullets, float recoilTime, float refillTime) :
        maxBullets{maxBullets},
        bullets{maxBullets},
        recoilTimer{recoilTime, "RecoilTimer"},
        refillTimer{refillTime, "RefillTimer"} {}
    ~Weapon() = default;

    void update(float deltaTime){
        recoilTimer.update(deltaTime);
        refillTimer.update(deltaTime);
        if(refillTimer.done() && bullets < maxBullets){
            bullets++;
            refillTimer.reset();
        }
    }

    bool fire() {
        if(ready()) {
            recoilTimer.reset();
            return true;
        }
        return false;
    }
    bool ready() {
        return recoilTimer.done() && bullets > 0;
    }
private:
    Timer recoilTimer;
    Timer refillTimer;
    int bullets;
    int maxBullets;
};