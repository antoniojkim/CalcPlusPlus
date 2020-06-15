
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

const Function::AbstractFunction* functions[Functions::numFunctions] = {
    &__Beta__, &__Betainc__, &__Cholesky__, &__LU__, &__LUsolve__, &__abs__, &__absdev__,
    &__acos__, &__acosh__, &__acot__, &__acoth__, &__acsc__, &__acsch__, &__acos__,
    &__acosh__, &__acot__, &__acoth__, &__acsc__, &__acsch__, &__acos__, &__acosh__,
    &__acot__, &__acoth__, &__acsc__, &__acsch__, &__asec__, &__asech__, &__asin__,
    &__asinh__, &__atan__, &__atanh__, &__argmax__, &__argmin__, &__asec__, &__asech__,
    &__asin__, &__asinh__, &__atan__, &__atanh__, &__asec__, &__asech__, &__asin__,
    &__asinh__, &__atan__, &__atanh__, &__lag1__, &__bin__, &__cb__, &__cbrt__, &__choose__,
    &__choose__, &__cos__, &__cosh__, &__cot__, &__coth__, &__csc__, &__csch__, &__cubic__,
    &__cubicc__, &__deg__, &__deriv__, &__det__, &__dfact__, &__diff__, &__exp__, &__exp2__,
    &__expm1__, &__fact__, &__fcmp__, &__fft__, &__frexp__, &__gamma__, &__gamma_inc__,
    &__gamma_inc_P__, &__gamma_inc_Q__, &__gamma_inc__, &__gamma_inc_P__, &__gamma_inc_Q__,
    &__gammainv__, &__gammastar__, &__gcd__, &__hex__, &__hypot__, &__ifft__, &__integral__,
    &__kurtosis__, &__kurtosis__, &__lag1__, &__lcm__, &__ldexp__, &__ln__, &__ln1p__,
    &__ln2__, &__lnBeta__, &__lnchoose__, &__lnchoose__, &__lndet__, &__lndfact__,
    &__lnfact__, &__lngamma__, &__lnpermute__, &__lnpermute__, &__lnpoch__, &__log__,
    &__log__, &__ln1p__, &__log1pm__, &__ln2__, &__logabs__, &__logn__, &__max__,
    &__argmax__, &__mean__, &__median__, &__min__, &__argmin__, &__neg__, &__num__,
    &__permute__, &__permute__, &__poch__, &__pochrel__, &__quad__, &__quadc__, &__rad__,
    &__sd__, &__sec__, &__sech__, &__sin__, &__sinh__, &__skew__, &__LUsolve__, &__sqr__,
    &__sqrt__, &__sd__, &__sd__, &__tan__, &__tanh__, &__taylorcoeff__, &__tss__, &__var__,
    &__var__
};

const Function::AbstractFunction* getFunction(const char* name){
    return functions[Functions::indexOf(name)];
}
const Function::AbstractFunction* getFunction(const int index){
    return functions[index];
}
