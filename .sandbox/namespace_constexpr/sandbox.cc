#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

template<class T, std::size_t N>
constexpr std::size_t array_size(T (&arr)[N])  {  return N;  }

namespace Function {
    constexpr const char* names[] = {
        "Exp", "Gauss", "Rand", "Var", "abs", "absdev", "acos", "acosh", "acot", "acoth",
        "acsc", "acsch", "arccos", "arccosh", "arccot", "arccoth", "arccsc", "arccsch",
        "arcosh", "arcoth", "arcsch", "arcsec", "arcsech", "arcsin", "arcsinh", "arctan",
        "arctanh", "argmax", "argmin", "arsech", "arsinh", "artanh", "asec", "asech", "asin",
        "asinh", "atan", "atanh", "autocorr", "beta", "betainc", "bin", "cb", "cbrt", "cdf",
        "cdfP", "cdfPinv", "cdfQ", "cdfQinv", "cdfinv", "choose", "cos", "cosh", "cot", "coth",
        "csc", "csch", "cubic", "cubicc", "deg", "deriv", "det", "dfact", "diff", "exp",
        "exp_2", "expm1", "fact", "fcmp", "fft", "frexp", "gamma", "gammainc", "gammaincp",
        "gammaincq", "gammainv", "gammastar", "gcd", "hex", "hypot", "icdf", "icdfP", "icdfQ",
        "ifft", "integral", "kurt", "kurtosis", "lag1", "lcm", "ldexp", "ln", "ln1p", "ln_2",
        "lnbeta", "lnchoose", "lndfact", "lnfact", "lngamma", "lnpermute", "lnpoch", "log",
        "log1p", "log_2", "logn", "max", "mean", "median", "min", "neg", "num", "pdf",
        "permute", "poch", "pochrel", "quad", "quadc", "rad", "rand", "randint", "randseed",
        "randu", "randup", "rseed", "sd", "sec", "sech", "sin", "sinh", "skew", "sqr", "sqrt",
        "std", "stdev", "tan", "tanh", "taylorcoeff", "tss", "var", "variance"
    };
    constexpr const int length = array_size(names);

    constexpr int indexOf(const char* name){
        int low = 0;
        int high = length - 1;
        while (true){
            if (low > high){
                return -1;
            }

            int mid = (low + high) / 2;
            int cmp = std::strcmp(name, names[mid]);
            if (cmp == 0){
                return mid;
            }
            else if (cmp < 0){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        return -1;
    }
    inline int indexOf(const std::string& name){
        return indexOf(name.c_str());
    }
}


int main(){
    int index = Function::indexOf("sin");
    cout << index << endl;
}
