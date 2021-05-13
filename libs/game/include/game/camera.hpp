#pragma once
//
// Created by flashie on 13.05.2021.
//
#include <math/utilits.hpp>
#include <memory>
#include <utility>
#include "objects.hpp"

namespace game {
    class Camera {
    public:
        Camera(std::shared_ptr<SpaceShip> ship, math::coords_t follow_pos) : _ship(std::move(ship)), _follow_pos(follow_pos) {};

        math::coords_t get_position(math::coords_t observe_pos);

        math::coords_t get_follow_position();

        void set_follow_position(math::coords_t follow_pos);

    private:
        std::shared_ptr<SpaceShip> _ship;
        math::coords_t _follow_pos;
    };
}

