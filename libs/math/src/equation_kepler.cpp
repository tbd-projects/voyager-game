#include <cmath>

#include "equation_kepler.hpp"

namespace math {

EquationKepler::EquationKepler(decimal_t eccentricity
                               , decimal_t mean_anomaly)
        : _eccentricity(eccentricity)
          , _mean_anomaly(mean_anomaly) {}

decimal_t EquationKepler::solve() const {
    if (_eccentricity == 0.0f) {
        return _mean_anomaly;
    }
    if (_eccentricity < 1.0f) {
        return base_solve();
    }
    if (_eccentricity == 1.0f) {
        return _mean_anomaly;
    }
    return hyp_solve();
}

decimal_t EquationKepler::base_solve() const {
    decimal_t e = _eccentricity;
    decimal_t M = _mean_anomaly;
    auto func = [e, M](decimal_t x)
            -> AlgebraicMethods::return_for_solve_equastion {
        AlgebraicMethods::return_for_solve_equastion res{
                M + e * std::sin(x) - x, e * std::cos(x) - 1, -e * std::sin(x)};
        return res;
    };

    AlgebraicMethods algebra;
    return algebra.solve_equastion_by_Halley(func, M, 8);
}

decimal_t EquationKepler::hyp_solve() const {
    decimal_t e = _eccentricity;
    decimal_t M = _mean_anomaly;
    auto func = [e, M](math::decimal_t x)
            -> AlgebraicMethods::return_for_solve_equastion {
        AlgebraicMethods::return_for_solve_equastion res{
                M + e * std::sinh(x) - x, e * std::cosh(x) - 1,
                e * std::sinh(x)};
        return res;
    };

    AlgebraicMethods algebra;
    decimal_t start_x = std::log(2 * M / e + 1.85f);
    return algebra.solve_equastion_by_Halley(func, start_x, 30);
}

}  // namespace math
