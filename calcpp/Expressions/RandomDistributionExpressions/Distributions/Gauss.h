#pragma once

#include <list>

#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

#include "../../../Utils/Random.h"
#include "../../Expression.h"
#include "../RandomDistributionDirectory.h"

double rand_Gauss(const std::list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        double sigma = args.front()->value(vars);
        return gsl_ran_gaussian(rng.get(), sigma);
    }
    return GSL_NAN;
}

double pdf_Gauss(double x, const std::list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        double sigma = args.front()->value(vars);
        return gsl_ran_gaussian_pdf(x, sigma);
    }
    return GSL_NAN;
}

double cdf_P_Gauss(double x, const std::list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        double sigma = args.front()->value(vars);
        return gsl_cdf_gaussian_P(x, sigma);
    }
    return GSL_NAN;
}

double cdf_Q_Gauss(double x, const std::list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        double sigma = args.front()->value(vars);
        return gsl_cdf_gaussian_Q(x, sigma);
    }
    return GSL_NAN;
}


double cdf_Pinv_Gauss(double x, const std::list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        double sigma = args.front()->value(vars);
        return gsl_cdf_gaussian_Pinv(x, sigma);
    }
    return GSL_NAN;
}

double cdf_Qinv_Gauss(double x, const std::list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        double sigma = args.front()->value(vars);
        return gsl_cdf_gaussian_Qinv(x, sigma);
    }
    return GSL_NAN;
}
