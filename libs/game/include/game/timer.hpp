//
// Created by flashie on 17.05.2021.
//
#pragma once

#include <ctime>
#include <chrono>

class ITimer {
public:
    ITimer() = default;

    virtual ~ITimer() = 0;

    virtual void start() = 0;

    virtual void stop() = 0;

    virtual void pause() = 0;

    virtual void unpause() = 0;

    virtual void reset() = 0;

    virtual std::chrono::milliseconds get_ms() = 0;

    virtual std::chrono::seconds get_s() = 0;
};

class Timer : public ITimer {
public:
    Timer() = default;

    void start() override;

    void stop() override;

    void reset() override;

    void pause() override;

    void unpause() override;

    std::chrono::milliseconds get_ms() override;

    std::chrono::seconds get_s() override;


private:
    std::chrono::steady_clock::time_point _start;
    std::chrono::steady_clock::time_point _pause;
    std::chrono::milliseconds _pause_sum;
    std::chrono::milliseconds _duration;
    bool _is_running;
    bool _is_pause;

};