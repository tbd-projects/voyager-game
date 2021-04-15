#include "utilits.hpp"
#include "vector2d.hpp"

namespace math {


//  ---------------------------------coords_t----------------------------------


coords_t::coords_t()
        : x(0)
          , y(0) {}

coords_t::coords_t(decimal_t v_x, decimal_t v_y)
        : x(v_x)
        , y(v_y) {}

bool coords_t::operator==(coords_t coords_t) const {
    return false;
}

coords_t coords_t::operator-(coords_t coords) const {
    return coords_t();
}

coords_t coords_t::operator+(coords_t coords) const {
    return coords_t();
}

coords_t &coords_t::operator-=(coords_t coords) {
    return *this;
}

coords_t &coords_t::operator+=(coords_t coords) {
    return *this;
}

coords_t coords_t::operator-(decimal_t offset) const {
    return coords_t();
}

coords_t coords_t::operator+(decimal_t offset) const {
    return coords_t();
}

coords_t &coords_t::operator-=(decimal_t offset) {
    return *this;
}

coords_t &coords_t::operator+=(decimal_t offset) {
    return *this;
}


//  ---------------------------Utilits-----------------------------------------


coords_t Utilits::rotate_point(coords_t point, decimal_t angle
                               , coords_t basis) {
    return coords_t();
}

bool Utilits::point_relative_line(Vector2d line, coords_t point) {
    return false;
}

}  // namespace math
