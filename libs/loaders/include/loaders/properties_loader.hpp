#pragma once

#include <cstddef>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "math.hpp"

namespace game {
    enum ship_character {
        BATTERY,
        ENGINE_PWR,
        FUEL,
        HEALTH,
        SPRITE_ID,
        ALL
    };

    struct properties_t {
        math::decimal_t fuel;
        unsigned int health;
        unsigned int battery;
        unsigned int engine_power;
        unsigned int sprite_id;

        bool is_empty() const {
            return math::Utilits::is_null(fuel) && !health && !battery && !engine_power && !sprite_id;
        }
        friend bool operator==(const properties_t &a, const properties_t &b) {
            return a.fuel == b.fuel && a.health == b.health && a.battery == b.battery &&
                   a.engine_power == b.engine_power && a.sprite_id == b.sprite_id;
        }

    };

    class PlayerPropertiesLoader {

    public:
        virtual properties_t load_current_properties(int player_id) = 0;

        virtual void save_current_properties(int player_id, properties_t &properties) = 0;

        virtual ~PlayerPropertiesLoader() = default;

    protected:
        std::string path;
        size_t _sprite_id;
        std::unique_ptr<math::Polygon> _pol;
    };

    class JsonPlayerPropertiesLoader : public PlayerPropertiesLoader {
    public:
        JsonPlayerPropertiesLoader() = delete;

        JsonPlayerPropertiesLoader(const std::string &root_path);

        properties_t load_current_properties(int player_id) override;

        void save_current_properties(int player_id, properties_t &properties) override;

        bool has_player(int player_id);

    };
} // namespace game

