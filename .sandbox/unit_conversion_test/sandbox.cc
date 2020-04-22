#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

#include <gsl/gsl_const_mksa.h>
#include <gsl/gsl_const_cgsm.h>
#include <gsl/gsl_const_num.h>

using namespace std;

int main(){
    cout << "GSL_CONST_MKSA_POUND_MASS: " << std::setprecision(16) << GSL_CONST_MKSA_POUND_MASS << endl;
    cout << "GSL_CONST_MKSA_OUNCE_MASS: " << std::setprecision(16) << GSL_CONST_MKSA_OUNCE_MASS << endl;
}
