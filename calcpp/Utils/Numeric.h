#pragma once

#include <gsl/gsl_complex.h>

#include "../Expressions/Types.h"

namespace calcpp {

#define IS_NAN(n) gsl_isnan((const double) n)
#define IS_INT(n) (std::trunc(n) == n)

    int compare(const Double n1, const Double n2, const double precision = 1e-15);

    int compare(
        const gsl_complex& c1, const gsl_complex& c2, const double precision = 1e-15);
    bool operator==(const gsl_complex& c1, const gsl_complex& c2);
    bool operator!=(const gsl_complex& c1, const gsl_complex& c2);

}  // namespace calcpp
