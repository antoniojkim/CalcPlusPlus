#include <cassert>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

constexpr const int numFunctions = 110;
constexpr const char* functionNames[numFunctions] = {
    "taylorcoeff", "lnpermute", "integrate", "gammastar", "gammaincq", "gammaincp",
	"variance", "lnchoose", "kurtosis", "integral", "gammainv", "gammainc", "autocorr",
	"pochrel", "permute", "lngamma", "lndfact", "betainc", "arctanh", "arcsinh", "arcsech",
	"arccsch", "arccoth", "arccosh", "median", "lnpoch", "lnfact", "lnbeta", "cubicc",
	"choose", "artanh", "arsinh", "arsech", "argmin", "argmax", "arctan", "arcsin",
	"arcsec", "arcsch", "arcoth", "arcosh", "arccsc", "arccot", "arccos", "absdev", "stdev",
	"quadc", "log_2", "log1p", "ldexp", "hypot", "gamma", "frexp", "expm1", "exp_2",
	"dfact", "deriv", "cubic", "atanh", "asinh", "asech", "acsch", "acoth", "acosh", "tanh",
	"sqrt", "skew", "sinh", "sech", "quad", "poch", "mean", "logn", "ln_2", "ln1p", "lag1",
	"kurt", "ifft", "fcmp", "fact", "csch", "coth", "cosh", "beta", "atan", "asin", "asec",
	"acsc", "acot", "acos", "var", "tss", "tan", "std", "sin", "sec", "neg", "min", "max",
	"log", "fft", "exp", "det", "csc", "cot", "cos", "abs", "sd", "ln", "dx"
};
constexpr const char * sortedFunctionNames[numFunctions] = {
    "abs", "absdev", "acos", "acosh", "acot", "acoth", "acsc", "acsch", "arccos", "arccosh",
    "arccot", "arccoth", "arccsc", "arccsch", "arcosh", "arcoth", "arcsch", "arcsec", "arcsech",
    "arcsin", "arcsinh", "arctan", "arctanh", "argmax", "argmin", "arsech", "arsinh", "artanh",
    "asec", "asech", "asin", "asinh", "atan", "atanh", "autocorr", "beta", "betainc", "choose",
    "cos", "cosh", "cot", "coth", "csc", "csch", "cubic", "cubicc", "deriv", "det", "dfact",
    "dx", "exp", "exp_2", "expm1", "fact", "fcmp", "fft", "frexp", "gamma", "gammainc",
    "gammaincp", "gammaincq", "gammainv", "gammastar", "hypot", "ifft", "integral", "integrate",
    "kurt", "kurtosis", "lag1", "ldexp", "ln", "ln1p", "ln_2", "lnbeta", "lnchoose", "lndfact",
    "lnfact", "lngamma", "lnpermute", "lnpoch", "log", "log1p", "log_2", "logn", "max", "mean",
    "median", "min", "neg", "permute", "poch", "pochrel", "quad", "quadc", "sd", "sec", "sech",
    "sin", "sinh", "skew", "sqrt", "std", "stdev", "tan", "tanh", "taylorcoeff", "tss", "var", "variance"
};

constexpr int getFunctionIndex(const char* name){
    for (int i = 0; i < numFunctions; ++i){
        if (std::strcmp(name, functionNames[i]) == 0){
            return i;
        }
    }
    return -1;
}
inline int getFunctionIndex(const std::string& name){
    return getFunctionIndex(name.c_str());
}

// Binary Search
int getFunctionIndex2(const char* name){
    int low = 0;
    int high = numFunctions - 1;
    while (true){
        if (low > high){
            return -1;
        }

        int mid = (low + high) / 2;
        int cmp = std::strcmp(name, sortedFunctionNames[mid]);
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
inline int getFunctionIndex2(const std::string& name){
    return getFunctionIndex2(name.c_str());
}

// // Lower Bound
// constexpr int getFunctionIndex3(const char* name){
//     auto first = sortedFunctionNames;
//     auto last = sortedFunctionNames + numFunctions;
//     auto first = std::lower_bound(first, last, name);
//     if ((first != last && !(str::cmp(name < *first)))){
//         return *first;
//     }
//     return -1;
// }
// inline int getFunctionIndex2(const std::string& name){
//     return getFunctionIndex2(name.c_str());
// }

typedef int (*func_t)(const std::string&);

double timeit(std::ostream& out, func_t f, const std::string& str){
    std::clock_t start = std::clock();

    size_t isum = 0;
    for (int i = 0; i<1000000; ++i){
        isum += f(str);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    out << isum << endl;
    return duration;

}

void timing_experiment(){
    ostringstream out;
    double time1 = 0;
    double time2 = 0;
    for (auto& name : functionNames){
        time1 += timeit(out, getFunctionIndex, name);
        time2 += timeit(out, getFunctionIndex2, name);
    }


    cout << "Total Time (Linear):  " << time1 << endl;
    cout << "Total Time (Binary):  " << time2 << endl;
}

int main(){

    // cout << "Linear Search: " << getFunctionIndex("kurt") << endl;
    // cout << "Binary Search: " << getFunctionIndex2("kurt") << endl;

    for (auto& name : functionNames){
        int index = getFunctionIndex(name);
        assert(index != -1);
        assert(std::strcmp(name, functionNames[index]) == 0);
    }
    for (auto& name : functionNames){
        int index = getFunctionIndex2(name);
        assert(index != -1);
        assert(std::strcmp(name, sortedFunctionNames[index]) == 0);
    }

    // timing_experiment();

}
