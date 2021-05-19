//
// Created by flashie on 17.05.2021.
//
#include "timer.hpp"

void Timer::start() {
    if (!_is_running) {
        this->_start = std::chrono::steady_clock::now();
        this->_is_running = true;
    }
}

void Timer::stop() {
    if (_is_running) {
        this->_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - this->_start);
        this->_is_running = false;
    }
}

void Timer::reset() {
    this->_pause_sum = std::chrono::milliseconds(0);
    this->_is_running = false;
    this->_is_pause = false;
    this->_duration = std::chrono::milliseconds(0);
}

void Timer::pause() {
    this->_pause = std::chrono::steady_clock::now();
    this->_is_running = false;
    this->_is_pause = true;
}

void Timer::unpause() {
    if (this->_is_pause) {
        this->_pause_sum = this->_pause_sum + std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - this->_pause);
        this->_is_running = true;
        this->_is_pause = false;
    }
}

std::chrono::milliseconds Timer::get_ms() {
    this->unpause();
    this->stop();
    return this->_duration - this->_pause_sum;
}

std::chrono::seconds Timer::get_s() {
    return std::chrono::duration_cast<std::chrono::seconds>(this->get_ms());
}

bool Timer::is_pause() {
    return this->_is_pause;
}

bool Timer::is_run() {
    return this->_is_running;
}

