#pragma once

#include <iostream>
#include <memory>
#include <graphics/sprite.h>


namespace game {

    class IGameObject {
    public:
        IGameObject() = default;

        virtual void set_sprite(std::unique_ptr<graphics::Sprite> sprite) = 0;

        virtual const std::unique_ptr<graphics::Sprite> &get_sprite() = 0;

        virtual void set_sprite_id(size_t id) = 0;

        virtual size_t get_sprite_id() = 0;

        virtual ~IGameObject() = default;

    protected:
        std::unique_ptr<graphics::Sprite> _sprite;
        size_t _sprite_id = 0;
    };
}

