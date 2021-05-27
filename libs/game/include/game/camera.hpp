// Дмитрий Варин
#pragma once
//
// Created by flashie on 13.05.2021.
//
#include <math/utilits.hpp>
#include <memory>
#include <utility>
#include <graphics/camera.h>
#include "objects.hpp"

namespace game {
    class Camera: public graphics::Camera {
    public:

        explicit Camera(std::shared_ptr<SpaceShip> ship) : _ship(std::move(ship)) {};


        void update();

        template<typename T>
        void apply_object(T &obj) {
            apply(*obj.get_sprite(), obj.get_pos());
        }

    private:
        std::shared_ptr<SpaceShip> _ship;
    };
}

