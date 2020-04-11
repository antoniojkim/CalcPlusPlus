#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef void (*func_t)();


#include <iostream>
#include <cmath>

using namespace std;

#include <gsl/gsl_math.h>
#include <gsl/gsl_integration.h>

double f (double x, void * params) {
  return sin(cos(x));
}

void integrate(){
    gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);

    double result, error;
    double expected = -4.0;
    double alpha = 1.0;

    gsl_function F;
    F.function = &f;
    F.params = &alpha;

    gsl_integration_qags (&F, 0, 1, 0, 1e-7, 1000, w, &result, &error);


    gsl_integration_workspace_free (w);
}

void timeit(func_t f){
    std::clock_t start = std::clock();

    for (int i = 0; i<100000; ++i){
        f();
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "duration: " << duration << " seconds" << endl;
}

int main(){
    timeit(integrate);
}
