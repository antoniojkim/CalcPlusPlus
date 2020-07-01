
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

#include "Functions/Basic.h"
#include "Functions/Calculus.h"
#include "Functions/ExpLogFunctions.h"
#include "Functions/FFT.h"
#include "Functions/LinAlg.h"
#include "Functions/Polynomial.h"
#include "Functions/SpecialFunctions.h"
#include "Functions/Statistics.h"
#include "Functions/TrigFunctions.h"
#include "Operators/Addition.h"
#include "Operators/Assignment.h"
#include "Operators/Bitwise.h"
#include "Operators/Division.h"
#include "Operators/Exponent.h"
#include "Operators/Factorial.h"
#include "Operators/Multiplication.h"
#include "Operators/Subtraction.h"
#include "AbstractFunction.h"
#include "Functions.h"

using namespace std;
using namespace Function;

const Function::AbstractFunction* functions[Functions::numFunctions] = {
    &Function::mod, &Function::bitwise_and, &Function::mul, &Function::pow, &Function::add,
    &Function::sub, &Function::div, &Function::floordiv, &Function::eq, &Function::eq,
    &Function::lshift, &Function::eq, &Function::rshift, &Function::Beta,
    &Function::Betainc, &Function::choose, &Function::Cholesky, &Function::LU,
    &Function::LUsolve, &Function::permute, &Function::pow, &Function::bitwise_xor,
    &Function::abs, &Function::absdev, &Function::acos, &Function::acosh, &Function::acot,
    &Function::acoth, &Function::acsc, &Function::acsch, &Function::acos, &Function::acosh,
    &Function::acot, &Function::acoth, &Function::acsc, &Function::acsch, &Function::acos,
    &Function::acosh, &Function::acot, &Function::acoth, &Function::acsc, &Function::acsch,
    &Function::asec, &Function::asech, &Function::asin, &Function::asinh, &Function::atan,
    &Function::atanh, &Function::argmax, &Function::argmin, &Function::asec,
    &Function::asech, &Function::asin, &Function::asinh, &Function::atan, &Function::atanh,
    &Function::asec, &Function::asech, &Function::asin, &Function::asinh, &Function::atan,
    &Function::atanh, &Function::lag1, &Function::bin, &Function::cb, &Function::cbrt,
    &Function::choose, &Function::choose, &Function::cos, &Function::cosh, &Function::cot,
    &Function::coth, &Function::csc, &Function::csch, &Function::cubic, &Function::cubicc,
    &Function::deg, &Function::deriv, &Function::det, &Function::dfact, &Function::diff,
    &Function::exp, &Function::exp2, &Function::expm1, &Function::fact, &Function::fcmp,
    &Function::fft, &Function::frexp, &Function::gamma, &Function::gamma_inc,
    &Function::gamma_inc_P, &Function::gamma_inc_Q, &Function::gamma_inc,
    &Function::gamma_inc_P, &Function::gamma_inc_Q, &Function::gammainv,
    &Function::gammastar, &Function::gcd, &Function::hex, &Function::hypot, &Function::ifft,
    &Function::integral, &Function::kurtosis, &Function::kurtosis, &Function::lag1,
    &Function::lcm, &Function::ldexp, &Function::ln, &Function::ln1p, &Function::ln2,
    &Function::lnBeta, &Function::lnchoose, &Function::lnchoose, &Function::lndet,
    &Function::lndfact, &Function::lnfact, &Function::lngamma, &Function::lnpermute,
    &Function::lnpermute, &Function::lnpoch, &Function::log, &Function::log,
    &Function::ln1p, &Function::log1pm, &Function::ln2, &Function::logabs, &Function::logn,
    &Function::max, &Function::argmax, &Function::mean, &Function::median, &Function::min,
    &Function::argmin, &Function::neg, &Function::num, &Function::permute,
    &Function::permute, &Function::poch, &Function::pochrel, &Function::quad,
    &Function::quadc, &Function::rad, &Function::sd, &Function::sec, &Function::sech,
    &Function::sin, &Function::sinh, &Function::skew, &Function::LUsolve, &Function::sqr,
    &Function::sqrt, &Function::sd, &Function::sd, &Function::tan, &Function::tanh,
    &Function::taylorcoeff, &Function::tss, &Function::var, &Function::var,
    &Function::bitwise_or
};

namespace Functions {
    const Function::AbstractFunction* getFunction(const char* name){
        return functions[Functions::indexOf(name)];
    }
    const Function::AbstractFunction* getFunction(const int index){
        return functions[index];
    }
}
