#pragma once

#include <cmath>

#include "../FunctionDirectory.h"


double f_neg(double x){ return -x; }
UnaryFunction f_abs = std::abs;
UnaryFunction f_sqrt = std::sqrt;
