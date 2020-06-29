
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
#include "Operators/Bitwise.h"
#include "Operators/Division.h"
#include "Operators/Exponent.h"
#include "Operators/Factorial.h"
#include "Operators/Multiplication.h"
#include "Operators/Subtraction.h"
#include "AbstractFunction.h"
#include "FunctionDispatch.h"

using namespace std;
using namespace Function;

const Function::AbstractFunction* functions[Functions::numFunctions] = {
    &mod, &and, &mul, &pow, &add, &sub, &div, &floordiv, &lshift, &rshift, &Beta, &Betainc,
    &choose, &Cholesky, &LU, &LUsolve, &permute, &pow, &xor, &abs, &absdev, &acos, &acosh,
    &acot, &acoth, &acsc, &acsch, &acos, &acosh, &acot, &acoth, &acsc, &acsch, &acos,
    &acosh, &acot, &acoth, &acsc, &acsch, &asec, &asech, &asin, &asinh, &atan, &atanh,
    &argmax, &argmin, &asec, &asech, &asin, &asinh, &atan, &atanh, &asec, &asech, &asin,
    &asinh, &atan, &atanh, &lag1, &bin, &cb, &cbrt, &choose, &choose, &cos, &cosh, &cot,
    &coth, &csc, &csch, &cubic, &cubicc, &deg, &deriv, &det, &dfact, &diff, &exp, &exp2,
    &expm1, &fact, &fcmp, &fft, &frexp, &gamma, &gamma_inc, &gamma_inc_P, &gamma_inc_Q,
    &gamma_inc, &gamma_inc_P, &gamma_inc_Q, &gammainv, &gammastar, &gcd, &hex, &hypot,
    &ifft, &integral, &kurtosis, &kurtosis, &lag1, &lcm, &ldexp, &ln, &ln1p, &ln2, &lnBeta,
    &lnchoose, &lnchoose, &lndet, &lndfact, &lnfact, &lngamma, &lnpermute, &lnpermute,
    &lnpoch, &log, &log, &ln1p, &log1pm, &ln2, &logabs, &logn, &max, &argmax, &mean,
    &median, &min, &argmin, &neg, &num, &permute, &permute, &poch, &pochrel, &quad, &quadc,
    &rad, &sd, &sec, &sech, &sin, &sinh, &skew, &LUsolve, &sqr, &sqrt, &sd, &sd, &tan,
    &tanh, &taylorcoeff, &tss, &var, &var, &or
};

const Function::AbstractFunction* getFunction(const char* name){
    return functions[Functions::indexOf(name)];
}
const Function::AbstractFunction* getFunction(const int index){
    return functions[index];
}
