#include <cmath>
#include <memory>
#include <numeric>

#include <gsl/gsl_cdf.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/NullExpression.h"
#include "../../Expressions/NumericalExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

namespace calcpp {

    namespace fexpr {
        const gsl_rng_type* T;
        typedef std::unique_ptr<gsl_rng, decltype(&gsl_rng_free)> unique_gsl_rng;
        static unique_gsl_rng setup_rand() {
            gsl_rng_env_setup();
            T = gsl_rng_default;
            return unique_gsl_rng(gsl_rng_alloc(T), gsl_rng_free);
        }

        const unique_gsl_rng r = setup_rand();

        // expression make_transformed_matrix(expression size, TransformerFunction f){
        //     if (size->isNumber()){
        //         double n = size->value();
        //         if (n <= 0){
        //             THROW_ERROR("Expected a positive size. Got: ", size);
        //         }
        //         if (std::trunc(n) != n){
        //             THROW_ERROR("Expected a integer size. Got: ", size);
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
        //                 THROW_ERROR("Expected a positive size. Got: ", size);
        //             }
        //             if (std::trunc(n) != n){
        //                 THROW_ERROR("Expected a integer size. Got: ", size);
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
        //                 THROW_ERROR("Expected a positive size. Got: ", size);
        //             }
        //             if (std::trunc(m) != m || std::trunc(n) != n){
        //                 THROW_ERROR("Expected a integer size. Got: ", size);
        //             }
        //             if (m == 1 && n == 1){
        //                 return f(None);
        //             }
        //             auto mat = MatrixExpression::construct((size_t) m, (size_t) n);
        //             mat->apply(f);
        //             return mat;
        //         }
        //     }
        //     THROW_ERROR("Expected positive integer or tuple size. Got: ", size);
        // }

        // @Function rand: random
        struct rand: public FunctionExpression {
            rand() : FunctionExpression("rand", {}) {}
            expression call(expression args) const override {
                return num(gsl_rng_uniform(r.get()));
            }
        };

        // @Function randn: gaussian
        struct randn: public FunctionExpression {
            randn() :
                FunctionExpression("randn", {kwarg("sigma", 1), kwarg("size", 1)}) {}
            expression call(expression args) const override {
                double sigma = (double) args->get(0);
                expression size = args->at(1);
                if (size == Type::TUPLE) {
                    THROW_ERROR("tuple size not yet supported for randn");
                } else if (size != Type::NUM || size->value() != 1) {
                    THROW_ERROR("size != 1 not yet supported for randn");
                }
                return num(gsl_ran_gaussian(r.get(), sigma));
            }
        };

        // @Function gauss_pdf
        struct gauss_pdf: public FunctionExpression {
            gauss_pdf() :
                FunctionExpression("gauss_pdf", {arg("x"), kwarg("sigma", 1)}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double sigma = (double) args->get(1);
                return num(gsl_ran_gaussian_pdf(x, sigma));
            }
        };

        // @Function gauss_P: normal
        struct gauss_P: public FunctionExpression {
            gauss_P() : FunctionExpression("gauss_p", {arg("x"), kwarg("sigma", 1)}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double sigma = (double) args->get(1);
                return num(gsl_cdf_gaussian_P(x, sigma));
            }
        };

        // @Function gauss_Pinv: normalinv norminv
        struct gauss_Pinv: public FunctionExpression {
            gauss_Pinv() :
                FunctionExpression("gauss_Pinv", {arg("x"), kwarg("sigma", 1)}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double sigma = (double) args->get(1);
                return num(gsl_cdf_gaussian_Pinv(x, sigma));
            }
        };

        // @Function gauss_Q: cnorm cnormal
        struct gauss_Q: public FunctionExpression {
            gauss_Q() : FunctionExpression("gauss_Q", {arg("x"), kwarg("sigma", 1)}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double sigma = (double) args->get(1);
                return num(gsl_cdf_gaussian_Q(x, sigma));
            }
        };

        // @Function gauss_Qinv: cnorminv cnormalinv
        struct gauss_Qinv: public FunctionExpression {
            gauss_Qinv() :
                FunctionExpression("gauss_Qinv", {arg("x"), kwarg("sigma", 1)}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double sigma = (double) args->get(1);
                return num(gsl_cdf_gaussian_Qinv(x, sigma));
            }
        };

        // @Function exponential
        struct exponential: public FunctionExpression {
            exponential() : FunctionExpression("exponential", {arg("mu")}) {}
            expression call(expression args) const override {
                double mu = (double) args->get(0);
                return num(gsl_ran_exponential(r.get(), mu));
            }
        };

        // @Function exponential_pdf: exp_pdf
        struct exponential_pdf: public FunctionExpression {
            exponential_pdf() :
                FunctionExpression("exponential_pdf", {arg("x"), arg("mu")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double mu = (double) args->get(1);
                return num(gsl_ran_exponential_pdf(x, mu));
            }
        };

        // @Function exponential_P: exp_P
        struct exponential_P: public FunctionExpression {
            exponential_P() :
                FunctionExpression("expression_P", {arg("x"), arg("mu")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double mu = (double) args->get(1);
                return num(gsl_cdf_exponential_P(x, mu));
            }
        };

        // @Function exponential_Pinv: exp_Pinv
        struct exponential_Pinv: public FunctionExpression {
            exponential_Pinv() :
                FunctionExpression("exponential_Pinv", {arg("x"), arg("mu")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double mu = (double) args->get(1);
                return num(gsl_cdf_exponential_Pinv(x, mu));
            }
        };

        // @Function exponential_Q: exp_Q
        struct exponential_Q: public FunctionExpression {
            exponential_Q() :
                FunctionExpression("exponential_Q", {arg("x"), arg("mu")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double mu = (double) args->get(1);
                return num(gsl_cdf_exponential_Q(x, mu));
            }
        };

        // @Function exponential_Qinv: exp_Qinv
        struct exponential_Qinv: public FunctionExpression {
            exponential_Qinv() :
                FunctionExpression("exponential_Qinv", {arg("x"), arg("mu")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double mu = (double) args->get(1);
                return num(gsl_cdf_exponential_Qinv(x, mu));
            }
        };

        // @Function chisq
        struct chisq: public FunctionExpression {
            chisq() : FunctionExpression("chisq", {arg("nu")}) {}
            expression call(expression args) const override {
                double nu = (double) args->get(0);
                return num(gsl_ran_chisq(r.get(), nu));
            }
        };
        MAKE_FUNCTION_EXPRESSION(chisq)

        // @Function chisq_pdf
        struct chisq_pdf: public FunctionExpression {
            chisq_pdf() : FunctionExpression("chisq_pdf", {arg("x"), arg("nu")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double nu = (double) args->get(1);
                return num(gsl_ran_chisq_pdf(x, nu));
            }
        };

        // @Function chisq_P
        struct chisq_P: public FunctionExpression {
            chisq_P() : FunctionExpression("chisq_P", {arg("x"), arg("nu")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double nu = (double) args->get(1);
                return num(gsl_cdf_chisq_P(x, nu));
            }
        };

        // @Function chisq_Pinv
        struct chisq_Pinv: public FunctionExpression {
            chisq_Pinv() : FunctionExpression("chisq_Pinv", {arg("x"), arg("nu")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double nu = (double) args->get(1);
                return num(gsl_cdf_chisq_Pinv(x, nu));
            }
        };

        // @Function chisq_Q
        struct chisq_Q: public FunctionExpression {
            chisq_Q() : FunctionExpression("chisq_Q", {arg("x"), arg("nu")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double nu = (double) args->get(1);
                return num(gsl_cdf_chisq_Q(x, nu));
            }
        };

        // @Function chisq_Qinv
        struct chisq_Qinv: public FunctionExpression {
            chisq_Qinv() : FunctionExpression("chisq_Qinv", {arg("x"), arg("nu")}) {}
            expression call(expression args) const override {
                double x = (double) args->get(0);
                double nu = (double) args->get(1);
                return num(gsl_cdf_chisq_Qinv(x, nu));
            }
        };
    }  // namespace fexpr

    namespace functions {
        // begin sourcegen functions
        const expression chisq = std::shared_ptr<fexpr::chisq>(new fexpr::chisq());
        const expression chisq_P = std::shared_ptr<fexpr::chisq_P>(new fexpr::chisq_P());
        const expression chisq_Pinv = std::shared_ptr<fexpr::chisq_Pinv>(new fexpr::chisq_Pinv());
        const expression chisq_Q = std::shared_ptr<fexpr::chisq_Q>(new fexpr::chisq_Q());
        const expression chisq_Qinv = std::shared_ptr<fexpr::chisq_Qinv>(new fexpr::chisq_Qinv());
        const expression chisq_pdf = std::shared_ptr<fexpr::chisq_pdf>(new fexpr::chisq_pdf());
        const expression exponential = std::shared_ptr<fexpr::exponential>(new fexpr::exponential());
        const expression exponential_P = std::shared_ptr<fexpr::exponential_P>(new fexpr::exponential_P());
        const expression exponential_Pinv = std::shared_ptr<fexpr::exponential_Pinv>(new fexpr::exponential_Pinv());
        const expression exponential_Q = std::shared_ptr<fexpr::exponential_Q>(new fexpr::exponential_Q());
        const expression exponential_Qinv = std::shared_ptr<fexpr::exponential_Qinv>(new fexpr::exponential_Qinv());
        const expression exponential_pdf = std::shared_ptr<fexpr::exponential_pdf>(new fexpr::exponential_pdf());
        const expression gauss_P = std::shared_ptr<fexpr::gauss_P>(new fexpr::gauss_P());
        const expression gauss_Pinv = std::shared_ptr<fexpr::gauss_Pinv>(new fexpr::gauss_Pinv());
        const expression gauss_Q = std::shared_ptr<fexpr::gauss_Q>(new fexpr::gauss_Q());
        const expression gauss_Qinv = std::shared_ptr<fexpr::gauss_Qinv>(new fexpr::gauss_Qinv());
        const expression gauss_pdf = std::shared_ptr<fexpr::gauss_pdf>(new fexpr::gauss_pdf());
        const expression rand = std::shared_ptr<fexpr::rand>(new fexpr::rand());
        const expression randn = std::shared_ptr<fexpr::randn>(new fexpr::randn());
        // end sourcegen
    }  // namespace functions

}  // namespace calcpp
