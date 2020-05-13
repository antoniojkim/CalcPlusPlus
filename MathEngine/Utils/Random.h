#pragma once

#include <memory>

#include <gsl/gsl_rng.h>

extern std::unique_ptr<gsl_rng, decltype(&gsl_rng_free)> rng;
