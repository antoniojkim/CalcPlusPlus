#include <cmath>
#include <memory>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

using namespace Scanner;


namespace Function {

    const gsl_rng_type * T;
    typedef std::unique_ptr<gsl_rng, decltype(&gsl_rng_free)> unique_gsl_rng;
    static unique_gsl_rng setup_rand(){
        gsl_rng_env_setup();
        T = gsl_rng_default;
        return unique_gsl_rng(gsl_rng_alloc(T), gsl_rng_free);
    }

    unique_gsl_rng r = setup_rand();

    // expression make_transformed_matrix(expression size, TransformerFunction f){
    //     if (size->isNumber()){
    //         double n = size->value();
    //         if (n <= 0){
    //             throw Exception("Expected a positive size. Got: ", size);
    //         }
    //         if (std::trunc(n) != n){
    //             throw Exception("Expected a integer size. Got: ", size);
    //         }
    //         if (n == 1){
    //             return f(None);
    //         }
    //         auto mat = MatrixExpression::construct(1, (size_t) n);
    //         mat->apply(f);
    //         return mat;
    //     }
    //     if (size == TUPLE){
    //         if (size->size() == 1){
    //             double n = size->at(0)->value();
    //             if (n <= 0){
    //                 throw Exception("Expected a positive size. Got: ", size);
    //             }
    //             if (std::trunc(n) != n){
    //                 throw Exception("Expected a integer size. Got: ", size);
    //             }
    //             if (n == 1){
    //                 return f(None);
    //             }
    //             auto mat = MatrixExpression::construct(1, (size_t) n);
    //             mat->apply(f);
    //             return mat;
    //         }
    //         if (size->size() == 2){
    //             double m = size->at(0)->value();
    //             double n = size->at(1)->value();
    //             if (m <= 0 || n <= 0){
    //                 throw Exception("Expected a positive size. Got: ", size);
    //             }
    //             if (std::trunc(m) != m || std::trunc(n) != n){
    //                 throw Exception("Expected a integer size. Got: ", size);
    //             }
    //             if (m == 1 && n == 1){
    //                 return f(None);
    //             }
    //             auto mat = MatrixExpression::construct((size_t) m, (size_t) n);
    //             mat->apply(f);
    //             return mat;
    //         }
    //     }
    //     throw Exception("Expected positive integer or tuple size. Got: ", size);
    // }


    // @Function rand: random
    struct rand: public FunctionExpression {
        rand(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {}) {}  // Signature: ()
        double value(const Variables& vars = emptyVars) const override {
            return gsl_rng_uniform(r.get());
        }
    };
    MAKE_FUNCTION_EXPRESSION(rand)


    // @Function randn: gaussian
    struct randn: public FunctionExpression {
        randn(int functionIndex, expression arg):
              FunctionExpression(functionIndex, arg, {
                  // Signature: (sigma=1, size=1)
                  {"sigma", NumExpression::construct(1)},
                  {"size", NumExpression::construct(1)}
              }) {}
        // expression eval(const Variables& vars = emptyVars) override {
        //     double sigma = arg->at(0)->value(vars);
        //     expression size = arg->at(1)->eval(vars);
        //     make_transformed_matrix(size, [sigma](expression e) -> expression {
        //         return NumExpression::construct(gsl_ran_gaussian(r.get(), sigma));
        //     });
        // }
        double value(const Variables& vars = emptyVars) const override {
            double sigma = arg->at(0)->value(vars);
            expression size = arg->at(1)->eval(vars);
            if (size->value() != 1){
                throw Exception("randn expected size 1. Got: ", size);
            }
            return gsl_ran_gaussian(r.get(), sigma);
        }
    };
    MAKE_FUNCTION_EXPRESSION(randn)


    // @Function gauss_pdf
    struct gauss_pdf: public FunctionExpression {
        gauss_pdf(int functionIndex, expression arg):
            FunctionExpression(
                functionIndex, arg,
                // Signature: (x, sigma=1)
                {
                    {"x", Empty},
                    {"sigma", NumExpression::construct(1)},
                }
            ) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double sigma = arg->at(1)->value(vars);
            return gsl_ran_gaussian_pdf(x, sigma);
        }
    };
    MAKE_FUNCTION_EXPRESSION(gauss_pdf)


    // @Function gauss_P: norm
    struct gauss_P: public FunctionExpression {
        gauss_P(int functionIndex, expression arg):
            FunctionExpression(
                functionIndex, arg,
                // Signature: (x, sigma=1)
                {
                    {"x", Empty},
                    {"sigma", NumExpression::construct(1)},
                }
            ) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double sigma = arg->at(1)->value(vars);
            return gsl_cdf_gaussian_P(x, sigma);
        }
    };
    MAKE_FUNCTION_EXPRESSION(gauss_P)


    // @Function gauss_Pinv: norminv
    struct gauss_Pinv: public FunctionExpression {
        gauss_Pinv(int functionIndex, expression arg):
            FunctionExpression(
                functionIndex, arg,
                // Signature: (x, sigma=1)
                {
                    {"x", Empty},
                    {"sigma", NumExpression::construct(1)},
                }
            ) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double sigma = arg->at(1)->value(vars);
            return gsl_cdf_gaussian_Pinv(x, sigma);
        }
    };
    MAKE_FUNCTION_EXPRESSION(gauss_Pinv)


    // @Function gauss_Q: cnorm
    struct gauss_Q: public FunctionExpression {
        gauss_Q(int functionIndex, expression arg):
            FunctionExpression(
                functionIndex, arg,
                // Signature: (x, sigma=1)
                {
                    {"x", Empty},
                    {"sigma", NumExpression::construct(1)},
                }
            ) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double sigma = arg->at(1)->value(vars);
            return gsl_cdf_gaussian_Q(x, sigma);
        }
    };
    MAKE_FUNCTION_EXPRESSION(gauss_Q)


    // @Function gauss_Qinv: norminv
    struct gauss_Qinv: public FunctionExpression {
        gauss_Qinv(int functionIndex, expression arg):
            FunctionExpression(
                functionIndex, arg,
                // Signature: (x, sigma=1)
                {
                    {"x", Empty},
                    {"sigma", NumExpression::construct(1)},
                }
            ) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double sigma = arg->at(1)->value(vars);
            return gsl_cdf_gaussian_Qinv(x, sigma);
        }
    };
    MAKE_FUNCTION_EXPRESSION(gauss_Qinv)


    // @Function exponential
    struct exponential: public FunctionExpression {
        exponential(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (mu)
                {"mu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double mu = arg->at(0)->value(vars);
            return gsl_ran_exponential(r.get(), mu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(exponential)


    // @Function exponential_pdf
    struct exponential_pdf: public FunctionExpression {
        exponential_pdf(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (x, mu)
                {"x", Empty},
                {"mu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double mu = arg->at(1)->value(vars);
            return gsl_ran_exponential_pdf(x, mu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(exponential_pdf)


    // @Function exponential_P: exp_P
    struct exponential_P: public FunctionExpression {
        exponential_P(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (x, mu)
                {"x", Empty},
                {"mu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double mu = arg->at(1)->value(vars);
            return gsl_cdf_exponential_P(x, mu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(exponential_P)


    // @Function exponential_Pinv: exp_Pinv
    struct exponential_Pinv: public FunctionExpression {
        exponential_Pinv(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (x, mu)
                {"x", Empty},
                {"mu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double mu = arg->at(1)->value(vars);
            return gsl_cdf_exponential_Pinv(x, mu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(exponential_Pinv)


    // @Function exponential_Q: exp_Q
    struct exponential_Q: public FunctionExpression {
        exponential_Q(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (x, mu)
                {"x", Empty},
                {"mu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double mu = arg->at(1)->value(vars);
            return gsl_cdf_exponential_Q(x, mu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(exponential_Q)


    // @Function exponential_Qinv: exp_Qinv
    struct exponential_Qinv: public FunctionExpression {
        exponential_Qinv(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (x, mu)
                {"x", Empty},
                {"mu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double mu = arg->at(1)->value(vars);
            return gsl_cdf_exponential_Qinv(x, mu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(exponential_Qinv)


    // @Function chisq
    struct chisq: public FunctionExpression {
        chisq(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (nu)
                {"nu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double nu = arg->at(0)->value(vars);
            return gsl_ran_chisq(r.get(), nu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(chisq)


    // @Function chisq_pdf
    struct chisq_pdf: public FunctionExpression {
        chisq_pdf(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (x, nu)
                {"x", Empty},
                {"nu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double nu = arg->at(1)->value(vars);
            return gsl_ran_chisq_pdf(x, nu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(chisq_pdf)


    // @Function chisq_P
    struct chisq_P: public FunctionExpression {
        chisq_P(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (x, nu)
                {"x", Empty},
                {"nu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double nu = arg->at(1)->value(vars);
            return gsl_cdf_chisq_P(x, nu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(chisq_P)


    // @Function chisq_Pinv
    struct chisq_Pinv: public FunctionExpression {
        chisq_Pinv(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (x, nu)
                {"x", Empty},
                {"nu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double nu = arg->at(1)->value(vars);
            return gsl_cdf_chisq_Pinv(x, nu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(chisq_Pinv)


    // @Function chisq_Q
    struct chisq_Q: public FunctionExpression {
        chisq_Q(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (x, nu)
                {"x", Empty},
                {"nu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double nu = arg->at(1)->value(vars);
            return gsl_cdf_chisq_Q(x, nu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(chisq_Q)


    // @Function chisq_Qinv
    struct chisq_Qinv: public FunctionExpression {
        chisq_Qinv(int functionIndex, expression arg):
            FunctionExpression(functionIndex, arg, {
                // Signature: (x, nu)
                {"x", Empty},
                {"nu", Empty}
            }) {}
        double value(const Variables& vars = emptyVars) const override {
            double x = arg->at(0)->value(vars);
            double nu = arg->at(1)->value(vars);
            return gsl_cdf_chisq_Qinv(x, nu);
        }
    };
    MAKE_FUNCTION_EXPRESSION(chisq_Qinv)
}
