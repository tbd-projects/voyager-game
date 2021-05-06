#include "equation_kepler.hpp"

namespace math {

EquationKepler::EquationKepler(decimal_t eccentricity
                               , decimal_t mean_anomaly)
        : _eccentricity(eccentricity)
          , _mean_anomaly(mean_anomaly) {}

decimal_t EquationKepler::solve() const {
    return 0;
}

decimal_t EquationKepler::base_solve() {
    return 0;
}

decimal_t EquationKepler::advance_solve() {
    return 0;
}

decimal_t EquationKepler::hyp_solve() {
    return 0;
}

}  // namespace math
