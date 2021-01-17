#pragma once

#include <gsl/gsl_complex.h>

namespace calcpp {
    int compare(double n1, double n2, double precision = 1e-15);

    int compare(const gsl_complex& c1, const gsl_complex& c2, double precision = 1e-15);
    bool operator==(const gsl_complex& c1, const gsl_complex& c2);
    bool operator!=(const gsl_complex& c1, const gsl_complex& c2);

}  // namespace calcpp
