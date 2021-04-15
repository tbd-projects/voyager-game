#pragma once

#include <unistd.h>
#include <memory>
#include "math.hpp"

namespace physics {

class Engine;

class IMovable {
  public:
    virtual void move(const Engine &physical_engine) = 0;
};

class ICollisionable {
  public:
    virtual bool check_collision(const ICollisionable &collision) const = 0;
};

class IInfluenceableByForce;

class IConnectToEngine {
  public:
    virtual void add_object(std::unique_ptr<IInfluenceableByForce> object) = 0;

    virtual void delete_object
                        (std::unique_ptr<IInfluenceableByForce> object) = 0;
};


class IInfluenceableByForce {
  public:
    IInfluenceableByForce() = delete;

    explicit IInfluenceableByForce(std::unique_ptr<Engine> engine);

    IInfluenceableByForce(const IInfluenceableByForce&) = delete;

    IInfluenceableByForce& operator=(const IInfluenceableByForce&) = delete;

    virtual math::coords_t get_position() const = 0;

    virtual math::Vector2d &get_velocity() = 0;

    virtual bool have_some_trust() const = 0;

    virtual math::decimal_t target_trust() const = 0;

    virtual void free_current_trust() = 0;

    virtual size_t get_weight() const = 0;

    virtual ~IInfluenceableByForce();

  private:
    friend class Engine;

    std::unique_ptr<Engine> _engine;
    ssize_t _index;
};

}  // namespace physics

