// Дмитрий Варин
#pragma once

namespace game {

    struct level_stat {
        unsigned int num;
        unsigned int time_as_seconds;
        unsigned char stars;
        bool is_win;

        bool operator==(const level_stat &b) const {
            return num == b.num && time_as_seconds == b.time_as_seconds &&
                   is_win == b.is_win && stars == b.stars;
        }

        level_stat() = default;

        level_stat(unsigned int num, unsigned int time, unsigned char stars, bool is_win) :
                num(num),
                time_as_seconds(time),
                stars(stars),
                is_win(is_win) {}
    };

    struct progress_t {
        size_t coins;
        std::vector<level_stat> levels;

        [[nodiscard]] bool is_empty() const {
            return !coins && levels.empty();
        }

        friend bool operator==(const progress_t &a, const progress_t &b) {
            bool is_eq = a.coins == b.coins;
            if (is_eq) {
                is_eq = a.levels.size() == b.levels.size();
                if (is_eq) {
                    for (size_t i = 0; (i < a.levels.size()) && is_eq; ++i) {
                        is_eq = a.levels[i] == b.levels[i];
                    }
                }
            }
            return is_eq;
        }
    };

    enum ship_character {
        BATTERY,
        ENGINE_PWR,
        FUEL,
        HEALTH,
        SPRITE_ID,
        ALL
    };

    struct ship_init_t {
        math::coords_t pos;
        math::Vector2d velocity;
        math::decimal_t density;
        size_t weight;

        ship_init_t() = default;

        ship_init_t(const math::coords_t pos, math::Vector2d velocity, math::decimal_t density, size_t weight) :
                pos(pos), velocity(velocity), density(density), weight(weight) {}

        bool operator==(const ship_init_t &b) const {
            return this->weight == b.weight && this->density == b.density && this->velocity == b.velocity &&
                   this->pos == b.pos;
        }
    };

    struct properties_t {
        math::decimal_t fuel;
        unsigned int health;
        unsigned int battery;
        unsigned int engine_power;
        unsigned int sprite_id;

        [[nodiscard]] bool is_empty() const {
            return math::Utilits::is_null(fuel) && !health && !battery && !engine_power && !sprite_id;
        }

        friend bool operator==(const properties_t &a, const properties_t &b) {
            return a.fuel == b.fuel && a.health == b.health && a.battery == b.battery &&
                   a.engine_power == b.engine_power && a.sprite_id == b.sprite_id;
        }

    };

}