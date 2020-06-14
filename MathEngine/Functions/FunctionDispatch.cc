
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

#include "Basic.h"
#include "Calculus.h"
#include "ExpLogFunctions.h"
#include "FFT.h"
#include "LinAlg.h"
#include "Polynomial.h"
#include "SpecialFunctions.h"
#include "Statistics.h"
#include "TrigFunctions.h"
#include "AbstractFunction.h"
#include "FunctionDispatch.h"

using namespace std;
using namespace Function;

const AbstractFunction* functions[Functions::numFunctions] = {
    &Beta, &Betainc, &Cholesky, &LU, &LUsolve, &abs, &absdev, &acos, &acosh, &acot, &acoth,
    &acsc, &acsch, &acos, &acosh, &acot, &acoth, &acsc, &acsch, &acos, &acosh, &acot,
    &acoth, &acsc, &acsch, &asec, &asech, &asin, &asinh, &atan, &atanh, &argmax, &argmin,
    &asec, &asech, &asin, &asinh, &atan, &atanh, &asec, &asech, &asin, &asinh, &atan,
    &atanh, &lag1, &bin, &cb, &cbrt, &choose, &choose, &cos, &cosh, &cot, &coth, &csc,
    &csch, &cubic, &cubicc, &deg, &deriv, &det, &dfact, &diff, &exp, &exp2, &expm1, &fact,
    &fcmp, &fft, &frexp, &gamma, &gammainc, &gammaincp, &gammaincq, &gammainc, &gammaincp,
    &gammaincq, &gammainv, &gammastar, &gcd, &hex, &hypot, &ifft, &integral, &kurtosis,
    &kurtosis, &lag1, &lcm, &ldexp, &ln, &ln1p, &ln2, &lnBeta, &lnchoose, &lnchoose, &lndet,
    &lndfact, &lnfact, &lngamma, &lnpermute, &lnpermute, &lnpoch, &log, &log, &ln1p,
    &log1pm, &ln2, &logabs, &logn, &max, &argmax, &mean, &median, &min, &argmin, &neg, &num,
    &permute, &permute, &poch, &pochrel, &quad, &quadc, &rad, &sd, &sec, &sech, &sin, &sinh,
    &skew, &LUsolve, &sqr, &sqrt, &sd, &sd, &tan, &tanh, &taylorcoeff, &tss, &var, &var
};

const AbstractFunction* getFunction(const char* name){
    return functions[Functions::indexOf(name)];
}
const AbstractFunction* getFunction(const int index){
    return functions[index];
}
