// Дмитрий Варин
#pragma once

#include "interface.hpp"
#include "physics/astronomical_object.hpp"

namespace game {
    class GameObject : public IGameObject, public physics::AstronomicalObject {
    public:

        explicit GameObject(size_t sprite_id, std::unique_ptr<graphics::Sprite> &&sprite, std::unique_ptr<math::Polygon> &&pol,
                            size_t weight, physics::Orbit::orbit_properties_t orbit) :
                physics::AstronomicalObject(std::move(pol), weight,orbit) {
            this->_sprite_id = sprite_id;
            this->_sprite = std::move(sprite);
        };

        explicit GameObject(size_t sprite_id, std::unique_ptr<graphics::Sprite> &&sprite, std::unique_ptr<math::Polygon> &&pol,
                            size_t weight, math::Vector2d velocity,
                            math::coords_t pos) : physics::AstronomicalObject(std::move(pol), weight, velocity, pos) {
            this->_sprite_id = sprite_id;
            this->_sprite = std::move(sprite);
        }

        const std::unique_ptr<graphics::Sprite> &get_sprite() override;

        void set_sprite(std::unique_ptr<graphics::Sprite> sprite) override;

        void set_sprite_id(size_t id) override;

        size_t get_sprite_id() override;


        GameObject() = delete;

        GameObject(const GameObject &) = delete;

        GameObject &operator=(const GameObject &) = delete;

    };


    class NotActiveObject : public IGameObject, public physics::PhysicalObject {
    public:
        NotActiveObject() = delete;

        NotActiveObject(const NotActiveObject &) = delete;

        NotActiveObject &operator=(const NotActiveObject &) = delete;

        const std::unique_ptr<graphics::Sprite> &get_sprite() override;

        void set_sprite(std::unique_ptr<graphics::Sprite> sprite) override;

        void set_sprite_id(size_t id) override;

        size_t get_sprite_id() override;

        explicit NotActiveObject(size_t sprite_id, std::unique_ptr<graphics::Sprite> &&sprite,
                                 std::unique_ptr<math::Polygon> &&pol,
                                 math::coords_t pos, math::Vector2d velocity, size_t weight) :
                physics::PhysicalObject(std::move(pol), pos, velocity, weight) {
            this->_sprite = std::move(sprite);
            this->_sprite_id = sprite_id;
        }

    };
} // namespace game
