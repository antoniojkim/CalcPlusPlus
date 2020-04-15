
#include <iostream>
#include <cmath>

using namespace std;

#include <gsl/gsl_math.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_integration.h>

double f (double x, void * params) {
  double f = sin(cos(x));
  return f;
}

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

    cout << endl;

    gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);

    gsl_function F;
    F.function = &f;
    a = 1;
    F.params = nullptr;

    double expected = -0.331357804676179563718495788580541555;
    double abserr;
    double result;
    size_t neval;

    int code = gsl_integration_qags(&F, 2, 32, 0, 1e-9, 1000, w, &result, &abserr);

    printf ("result          = % .18f\n", result);
    printf ("exact result    = % .18f\n", expected);
    printf ("estimated error = % .18f\n", abserr);
    printf ("actual error    = % .18f\n", result - expected);
    printf ("intervals       = %zu\n", w->size);

    gsl_integration_workspace_free (w);
}
