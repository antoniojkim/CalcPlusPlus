#pragma once

#include <list>
#include <vector>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_complex.h>

#include "../Expressions/Expression.h"
#include "../Expressions/InvalidExpression.h"
#include "../Expressions/MatrixExpression.h"
#include "../Expressions/TupleExpression.h"
#include "../Utils/Argparse.h"
#include "AbstractFunction.h"

#define MAKE_UNIQUE_GSL(F) \
    typedef std::unique_ptr<gsl_##F, decltype(&gsl_##F##_free)> unique_##F; \
    unique_##F make_unique_##F(size_t n){ \
        return unique_##F(gsl_##F##_alloc(n), gsl_##F##_free); \
    }

MAKE_UNIQUE_GSL(fft_real_workspace)
MAKE_UNIQUE_GSL(fft_real_wavetable)
MAKE_UNIQUE_GSL(fft_halfcomplex_wavetable)
MAKE_UNIQUE_GSL(fft_complex_workspace)
MAKE_UNIQUE_GSL(fft_complex_wavetable)

inline std::unique_ptr<double[]> make_complex_packed_array(size_t n){
    return std::make_unique<double[]>(n * 2);
}

namespace Functions {
    // @Function fft
    const struct: public NamedFunction {
        expression fft(const MatrixExpression* matrix){
            if (matrix && (matrix->rows() == 1 || matrix->cols() == 1)){
                size_t N = matrix->rows() * matrix->cols();
                auto work = make_unique_fft_real_workspace(N);
                if (matrix->isComplex()){
                    auto gsl_mat = matrix->to_gsl_matrix_complex();
                    auto data = make_complex_packed_array(N);
                    for (size_t i = 0; i < N; ++i){
                        data.get()[2*i] = GSL_REAL(gsl_matrix_complex_get(gsl_mat.get(), 0, i));
                        data.get()[2*i+1] = GSL_IMAG(gsl_matrix_complex_get(gsl_mat.get(), 0, i));
                    }

                    auto work = make_unique_fft_complex_workspace(N);
                    auto complextable = make_unique_fft_complex_wavetable(N);
                    gsl_fft_complex_forward(data.get(), 1, N, complextable.get(), work.get());

                    auto result = make_gsl_matrix_complex(1, N);
                    for (size_t i = 0; i < N; ++i){
                        gsl_matrix_complex_set(result.get(), 0, i,
                                               gsl_complex{data.get()[2*i], data.get()[2*i+1]});
                    }
                    return MatrixExpression::construct(result.get());
                }
                else{
                    auto gsl_mat = matrix->to_gsl_matrix();

                    auto real = make_unique_fft_real_wavetable(N);
                    gsl_fft_real_transform(gsl_mat->data, 1, N, real.get(), work.get());

                    auto data = make_complex_packed_array(N);
                    gsl_fft_halfcomplex_unpack(gsl_mat->data, data.get(), 1, N);

                    auto result = make_gsl_matrix_complex(1, N);
                    for (size_t i = 0; i < N; ++i){
                        gsl_matrix_complex_set(result.get(), 0, i,
                                               gsl_complex{data.get()[2*i], data.get()[2*i+1]});
                    }
                    return MatrixExpression::construct(result.get());
                }
            }
            return InvalidExpression::construct(Exception("FFT expected 1D Matrix."));
        }

        expression evaluate(expression e) override {
            ParsedArgs args(e);

            if (args.size() > 1){
                std::list<expression> exprs;
                for (auto& arg : *tuple){
                    exprs.emplace_back(arg->evaluate());
                }
                auto expr = MatrixExpression::construct(std::move(exprs), 1, exprs.size());
                return this->fft(expr->matrix());
            }
            return this->fft(args[0]->matrix());
        }
    } fft ("fft");

    // @Function ifft
    const struct: public NamedFunction {
        expression ifft(const MatrixExpression* matrix){
            if (matrix && (matrix->rows() == 1 || matrix->cols() == 1)){
                size_t N = matrix->rows() * matrix->cols();
                auto work = make_unique_fft_real_workspace(N);
                if (matrix->isComplex()){
                    auto gsl_mat = matrix->to_gsl_matrix_complex();
                    auto data = make_complex_packed_array(N);
                    for (size_t i = 0; i < N; ++i){
                        data.get()[2*i] = GSL_REAL(gsl_matrix_complex_get(gsl_mat.get(), 0, i));
                        data.get()[2*i+1] = GSL_IMAG(gsl_matrix_complex_get(gsl_mat.get(), 0, i));
                    }

                    auto work = make_unique_fft_complex_workspace(N);
                    auto complextable = make_unique_fft_complex_wavetable(N);
                    gsl_fft_complex_inverse(data.get(), 1, N, complextable.get(), work.get());

                    auto result = make_gsl_matrix_complex(1, N);
                    for (size_t i = 0; i < N; ++i){
                        gsl_matrix_complex_set(result.get(), 0, i,
                                                gsl_complex{data.get()[2*i], data.get()[2*i+1]});
                    }
                    return MatrixExpression::construct(result.get());
                }
                else{
                    auto gsl_mat = matrix->to_gsl_matrix();

                    auto data = make_complex_packed_array(N);
                    gsl_fft_real_unpack(gsl_mat->data, data.get(), 1, N);

                    auto halfcomplex = make_unique_fft_halfcomplex_wavetable(N);
                    gsl_fft_halfcomplex_inverse(data.get(), 1, N, halfcomplex.get(), work.get());

                    auto result = make_gsl_matrix_complex(1, N);
                    for (size_t i = 0; i < N; ++i){
                        gsl_matrix_complex_set(result.get(), 0, i,
                                                gsl_complex{data.get()[2*i], data.get()[2*i+1]});
                    }
                    return MatrixExpression::construct(result.get());
                }
            }
            return InvalidExpression::construct(Exception("IFFT expected 1D Matrix."));
        }

        expression evaluate(expression e) override {
            ParsedArgs args(e);

            if (args.size() > 1){
                std::list<expression> exprs;
                for (auto& arg : *tuple){
                    exprs.emplace_back(arg->evaluate());
                }
                auto expr = MatrixExpression::construct(std::move(exprs), 1, exprs.size());
                return this->ifft(expr->matrix());
            }
            return this->ifft(args[0]->matrix());
        }
    } ifft ("ifft");
}
