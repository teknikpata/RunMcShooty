#pragma once
#include <string>

class Timer {
 public:
  explicit Timer(float maxValue, std::string name)
      : maxValue{maxValue}, currentTime{maxValue}, name{std::move(name)} {}

  ~Timer() = default;

  void reset() { currentTime = maxValue; }

  bool done() const { return currentTime <= 0; }

  void update(float deltaTime) {
    if (currentTime >= 0) {
      currentTime -= deltaTime;
    }
  }

  std::string toString() {
    return "Timer {name: (" + name + ") currentTime: (" + std::to_string(currentTime) + ") maxValue: (" + std::to_string(maxValue) + ")}";
  }

 private:
  float maxValue;
  float currentTime;
  std::string name;
};