
#include <iostream>

using namespace std;

#include <gsl/gsl_poly.h>

int main(int argc, char** argv){
    double a = 6, b = -4, c = -7;
    double x0, x1;
    int numRoots = gsl_poly_solve_quadratic(a, b, c, &x0, &x1);
    switch(numRoots){
        case 2:
            cout << "x1: " << x1 << endl;
        case 1:
            cout << "x0: " << x0 << endl;
            break;
        default:
            cout << "No Roots" << endl;
    }
}
