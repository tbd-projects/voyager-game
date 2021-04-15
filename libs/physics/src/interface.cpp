#include "engine.hpp"
#include "interface.hpp"
#include "astronimical_object.hpp"

namespace physics {

IInfluenceableByForce::IInfluenceableByForce(std::unique_ptr<Engine> engine)
        : _engine(std::move(engine))
        , _index(-1) {
    _engine->add_object(
            static_cast<std::unique_ptr<IInfluenceableByForce>>(this));
}

IInfluenceableByForce::~IInfluenceableByForce() {
    _engine->delete_object(
            static_cast<std::unique_ptr<IInfluenceableByForce>>(this));
}

}  // namespace physics
