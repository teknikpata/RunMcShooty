#pragma once

#include <string>

class Event {
public:
    enum class Type {
        Input,
        Move,
        Attack
    };

    Event(Type type) : type{type} {}
    Event() = default;
    ~Event() = default;

    virtual std::string ToString() = 0;

    Type type;
};

class InputEvent : public Event {
public:
    InputEvent() : Event(Event::Type::Input) {}
    ~InputEvent() = default;

    std::string ToString() override {
        return "Im a InputEvent";
    }
};

class MoveEvent : public Event {
public:
    MoveEvent() : Event(Event::Type::Move) {}
    ~MoveEvent() = default;

    std::string ToString() override {
        return "Im a MoveEvent";
    }
};

class AttackEvent : public Event {
public:
    AttackEvent() : Event(Event::Type::Attack) {}
    ~AttackEvent() = default;

    std::string ToString() override {
        return "Im a AttackEvent";
    }
};
