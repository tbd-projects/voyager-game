// Дмитрий Варин
#pragma once

#include "main_object.hpp"
#include "physics/astronomical_object.hpp"
#include "game/interface.hpp"

namespace game {

class SpaceShip : public GameObject {
public:
    SpaceShip(
            size_t sprite_id,
            std::unique_ptr<graphics::Sprite> &&sprite,
            std::unique_ptr<math::Polygon> &&pol,
            properties_t &properties,
            math::decimal_t base_discard_pf_fuel,
            size_t weight,
            math::Vector2d velocity,
            math::coords_t pos)
            : GameObject(sprite_id, std::move(sprite),
                         std::move(pol), weight,
                         velocity, pos),
              _properties(properties) {
        this->_fuel_prop._base_discarder_mass_of_fuel = \
                    base_discard_pf_fuel;
    }

    ~SpaceShip() override = default;

    SpaceShip(const SpaceShip &ship) = delete;

    SpaceShip &operator=(const SpaceShip &ship) = delete;

    const properties_t &get_properties();

    void set_properties(properties_t &properties);

    [[nodiscard]] size_t get_fuel() const;

    [[nodiscard]] size_t get_health() const;

    [[nodiscard]] size_t get_battery() const;

    [[nodiscard]] size_t get_engine() const;

    [[nodiscard]] math::decimal_t get_fuel_density() const;

    void set_fuel(size_t fuel);

    void set_health(size_t health);

    void set_battery(size_t battery);

    void set_engine(size_t engine);

    void set_fuel_density(math::decimal_t fuel_density);

    bool update_fuel();

    bool update_battery();

    bool is_live();

    bool is_die();

    private:
        properties_t _properties;
        struct fuel_t {
            math::decimal_t _base_discarder_mass_of_fuel;
            math::decimal_t _fuel_density;
        } _fuel_prop;
    };

class SpaceBody : public GameObject {
public:
    SpaceBody() = delete;

    SpaceBody(size_t sprite_id, std::unique_ptr<graphics::Sprite> &&sprite,
              std::unique_ptr<math::Polygon> &&pol, size_t weight,
              physics::Orbit::orbit_properties_t orbit) :
            GameObject(sprite_id, std::move(sprite),
                       std::move(pol), weight,
                       orbit) {}

    SpaceBody(const SpaceBody &obj) = delete;

    SpaceBody &operator=(const SpaceBody &obj) = delete;

    ~SpaceBody() override = default;
    };

class Star : public NotActiveObject {
public:
    Star() = delete;

    Star(size_t sprite_id, std::unique_ptr<graphics::Sprite> &&sprite,
         std::unique_ptr<math::Polygon> &&pol, math::coords_t pos,
         math::Vector2d velocity, size_t weight) :
            NotActiveObject(sprite_id, std::move(sprite),
                            std::move(pol), pos,
                            velocity, weight) {}

    Star(const Star &) = delete;

    Star &operator=(const Star &obj) = delete;

    ~Star() override = default;
};

}  // namespace game

