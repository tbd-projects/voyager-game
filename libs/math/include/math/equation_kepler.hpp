#pragma once

#include <math/utilits.hpp>

namespace math {

class EquationKepler {
  public:
    EquationKepler(decimal_t eccentricity, decimal_t mean_anomaly);

    [[nodiscard]]
    decimal_t solve() const;

  private:
    decimal_t _eccentricity;
    decimal_t _mean_anomaly;

    [[nodiscard]]
    decimal_t base_solve() const;

    [[nodiscard]]
    decimal_t hyp_solve() const;
};

}  // namespace math
