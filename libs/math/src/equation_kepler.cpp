#include <cmath>

#include <debug/exception.hpp>

#include "equation_kepler.hpp"

namespace math {

EquationKepler::EquationKepler(decimal_t eccentricity
                               , decimal_t mean_anomaly)
        : _eccentricity(eccentricity)
          , _mean_anomaly(mean_anomaly) {
    if (std::abs(_mean_anomaly) > const_2_pi) {
        throw debug::ARG_ARGUMENT_ERROR("mean anomaly increase 2pi"
                                        + std::to_string(_mean_anomaly));
    }

    if (_eccentricity < 0) {
        throw debug::ARG_ARGUMENT_ERROR("eccentricity is negative"
                                        ", it's impossible"
                                        + std::to_string(_eccentricity));
    }
}

decimal_t EquationKepler::solve() const {
    if (_eccentricity == decm(0)) {
        return _mean_anomaly;
    }
    if (_eccentricity < decm(1.)) {
        return base_solve();
    }
    if (_eccentricity == decm(1.)) {
        return _mean_anomaly;
    }
    return hyp_solve();
}

decimal_t EquationKepler::base_solve() const {
    decimal_t e = _eccentricity;
    decimal_t M = _mean_anomaly;
    auto func = [e, M](decimal_t x)
            -> AlgebraicMethods::return_for_solve_equastion {
        math::decimal_t e_cos_x = e * std::cos(x);
        math::decimal_t e_sin_x = e * std::sin(x);
        return {-M - e_sin_x + x, -e * e_cos_x + 1, e_sin_x};
    };

    AlgebraicMethods algebra;
    return algebra.solve_equastion_by_Halley(func, M, 20);
}

decimal_t EquationKepler::hyp_solve() const {
    decimal_t e = _eccentricity;
    decimal_t M = _mean_anomaly;
    auto func = [e, M](math::decimal_t x)
            -> AlgebraicMethods::return_for_solve_equastion {
        math::decimal_t e_ch_x = e * std::cosh(x);
        math::decimal_t e_sh_x = e * std::sinh(x);
        return {-M + e_sh_x - x, e_ch_x - 1, e_sh_x};
    };

    AlgebraicMethods algebra;
    decimal_t start_x = std::log(2 * M / e + decm(1.85));

    if (std::isnan(start_x)) {
        start_x = M;
    }

    return algebra.solve_equastion_by_Halley(func, start_x, 30);
}

}  // namespace math
