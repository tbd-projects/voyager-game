#pragma once

#include <vector>
#include <set>
#include <memory>

#include <physics/interface.hpp>
#include <physics/mechanic.hpp>
#include <math.hpp>

namespace physics {

#define COLLIDE_DISTANCE 100

class PhysicalObject;
class EnginesIndexedObject;

class StoreObject: public IConnectToEngine {
  public:
    StoreObject() = default;

    void add_object(std::weak_ptr<PhysicalObject> object) override;

    void delete_object(std::weak_ptr<PhysicalObject> object) override;

    [[nodiscard]]
    bool contain_object(const PhysicalObject &object) const;

    [[nodiscard]]
    bool is_objects_with_equal_id(const PhysicalObject& object_1
                                 , const PhysicalObject& object_2) const;

    [[nodiscard]]
    std::vector<std::weak_ptr<PhysicalObject>> get_active_object() const;

  private:
    std::vector<std::weak_ptr<PhysicalObject>> _objects;

    std::set<size_t> _deleted_objects;
};

class Engine : public IConnectToEngine {
  public:
    Engine();

    explicit Engine(const Force& force);

    [[nodiscard]]
    math::Vector2d calc_force_by_object(PhysicalObject &object) const;

    [[nodiscard]]
    math::decimal_t get_effective_circle_orbit
                                (const PhysicalObject& object) const;

    [[nodiscard]]
    bool check_collision(const PhysicalObject& object) const;

    void add_object(std::weak_ptr<PhysicalObject> object) override;

    void delete_object(std::weak_ptr<PhysicalObject> object) override;

  private:
    const size_t _tick_of_calc;
    Mechanic _mechanic;
    StoreObject _objects;
};

}  // namespace physics
