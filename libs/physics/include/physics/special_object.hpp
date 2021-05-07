//This file is interface written by Artem Vetoshkin
#pragma once

#include <physics/interface.hpp>
#include <math.hpp>

namespace physics {

    class EnginesIndexedObject {
    public:
        EnginesIndexedObject();

        virtual ~EnginesIndexedObject() = default;

        friend class EngineStoreObject;
        friend class Engine;

    protected:
        ssize_t _index;
    };

    class AcceleratableObject {
    public:
        AcceleratableObject();

        [[nodiscard]]
        bool have_some_trust() const noexcept;

        [[nodiscard]]
        math::decimal_t target_trust() const noexcept;

        void add_trust(math::decimal_t target);

        void complete_add_trust();

        virtual ~AcceleratableObject() = default;

    private:
        bool _need_trust;
        math::decimal_t _target_trust;
    };

    class ColideObject : public math::IPositionable {
    public:
        ColideObject() = delete;

        explicit ColideObject(std::unique_ptr<math::Polygon> &&polygon);

        [[nodiscard]]
        bool is_colide(const ColideObject &object) const;

        [[nodiscard]]
        math::coords_t get_pos() const noexcept final;

        void set_pos(math::coords_t pos) final;

        std::unique_ptr<math::Polygon>& get_polygon();

    protected:
        std::unique_ptr<math::Polygon> _polygon;
    };

}  // namespace physics
