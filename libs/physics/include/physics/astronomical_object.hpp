//This file is interface written by Artem Vetoshkin
#pragma once

#include <memory>
#include <physics/interface.hpp>
#include <physics/engine.hpp>
#include <physics/orbit.hpp>
#include <math.hpp>

namespace physics {

    class AstronomicalObject : public IMovable, public PhysicalObject {
    public:
        AstronomicalObject() = delete;

        explicit AstronomicalObject(std::unique_ptr<math::Polygon> &&polygon);

        explicit AstronomicalObject(std::unique_ptr<math::Polygon> &&polygon
                , size_t weight
                , math::Vector2d velocity, math::coords_t pos);

        explicit AstronomicalObject(std::unique_ptr<math::Polygon> &&
                , size_t weight
                , math::Vector2d velocity, math::coords_t pos
                , Orbit::orbit_properties_t orbit) {};

        [[nodiscard]] constexpr const Orbit &get_orbit() const noexcept;

        void relocate_on_orbit(math::decimal_t angle);

        ~AstronomicalObject() override = default;

        void move(const Engine &physical_engine) override;

    private:
        Orbit _orbit;
    };


    }

}  // namespace physics
