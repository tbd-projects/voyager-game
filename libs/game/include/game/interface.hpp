#pragma once

#include <iostream>
#include <memory>
#include <graphics/sprite.h>
#include <game/structs.hpp>

namespace game {

    class SpaceBody;
    class Star;

    class CreatorLevel {
      public:
        virtual void create_level(size_t level_num) = 0;

        virtual size_t get_levels_count() = 0;

        virtual std::vector<std::shared_ptr<SpaceBody>> &&get_planets() = 0;

        virtual std::vector<std::shared_ptr<Star>> &&get_stars() = 0;

        virtual size_t get_bg_id() const = 0;

        virtual math::decimal_t get_fuel_density() const = 0;

        virtual ~CreatorLevel() = default;
    };

    class ProgressLoader {
      public:
        virtual progress_t load(size_t player_id) = 0;

        virtual void save(size_t player_id, progress_t &progress) = 0;

        virtual ~ProgressLoader() = default;
    };

    class PlayerPropertiesLoader {
      public:
        virtual properties_t load_current_properties(int player_id) = 0;

        virtual void save_current_properties(int player_id, properties_t &properties) = 0;

        virtual ~PlayerPropertiesLoader() = default;
    };

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

