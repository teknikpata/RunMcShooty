#pragma once

#include <queue>

template<class Object>
class RestrictedQueue {
public:
    RestrictedQueue(std::queue<Object>& queue) : queue{queue} {};
    ~RestrictedQueue() = default;

    void push(Object o) {
        queue.push(std::move(o));
    }

    template<class... Args>
    void emplace(Args&& ... args) {
        queue.emplace(args...);
    }

private:
    std::queue<Object>& queue;
};