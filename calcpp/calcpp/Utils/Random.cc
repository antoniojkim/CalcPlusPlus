#include <memory>

#include "Random.h"

gsl_rng* make_rng(){
    gsl_rng_env_setup();
    return gsl_rng_alloc(gsl_rng_default);
}
std::unique_ptr<gsl_rng, decltype(&gsl_rng_free)> rng (make_rng(), gsl_rng_free);
