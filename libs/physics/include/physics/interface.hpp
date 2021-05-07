//This file is interface written by Artem Vetoshkin
#pragma once

#include <unistd.h>
#include <vector>
#include <memory>

#include "math.hpp"

namespace physics {

    class Engine;

    class IMovable {
    public:
        virtual void move(const Engine &physical_engine) = 0;

        virtual ~IMovable() = default;
    };

    class PhysicalObject;

    class IConnectToEngine {
    public:
        virtual void add_object(std::weak_ptr<PhysicalObject> object) = 0;

        virtual void delete_object(std::weak_ptr<PhysicalObject> object) = 0;

        virtual ~IConnectToEngine() = default;
    };

    class PhysicalObject;

    class Force {
    public:
        [[nodiscard]]
        virtual math::Vector2d get_force(PhysicalObject &object
                , const std::vector<std::reference_wrapper<PhysicalObject>>
                                         &other_objects) const = 0;

        virtual ~Force() = default;
    };

}  // namespace physics

