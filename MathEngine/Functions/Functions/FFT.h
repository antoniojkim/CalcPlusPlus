#pragma once

#include <list>
#include <vector>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_complex.h>

#include "../../Expressions/Expression.h"
#include "../../Expressions/InvalidExpression.h"
#include "../../Expressions/MatrixExpression.h"
#include "../../Expressions/TupleExpression.h"
#include "../../Utils/Argparse.h"
#include "../AbstractFunction.h"

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

namespace Function {
    // @Function fft
    const struct __fft__: public Function::AbstractFunction {
        __fft__(): AbstractFunction("fft", "(m,)") {}

        expression eval(Function::Args& args) const override {
            using Scanner::MATRIX;
            auto matrix = args["m"];
            if (matrix == MATRIX && (matrix->shape(0) == 1 || matrix->shape(1) == 1)){
                size_t N = matrix->size();
                auto work = make_unique_fft_real_workspace(N);
                if (matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
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
                    return MatrixExpression::construct(result);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);

                    auto real = make_unique_fft_real_wavetable(N);
                    gsl_fft_real_transform(gsl_mat->data, 1, N, real.get(), work.get());

                    auto data = make_complex_packed_array(N);
                    gsl_fft_halfcomplex_unpack(gsl_mat->data, data.get(), 1, N);

                    auto result = make_gsl_matrix_complex(1, N);
                    for (size_t i = 0; i < N; ++i){
                        gsl_matrix_complex_set(result.get(), 0, i,
                                               gsl_complex{data.get()[2*i], data.get()[2*i+1]});
                    }
                    return MatrixExpression::construct(result);
                }
            }
            throw Exception("FFT expected 1D Matrix. Got: ", matrix);
        }
    } fft;

    // @Function ifft
    const struct __ifft__: public Function::AbstractFunction {
        __ifft__(): AbstractFunction("ifft", "(m,)") {}

        expression eval(Function::Args& args) const override {
            using Scanner::MATRIX;
            auto matrix = args["m"];
            if (matrix == MATRIX && (matrix->shape(0) == 1 || matrix->shape(1) == 1)){
                size_t N = matrix->size();
                auto work = make_unique_fft_real_workspace(N);
                if (matrix->isComplex()){
                    auto gsl_mat = to_gsl_matrix_complex(matrix);
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
                    return MatrixExpression::construct(result);
                }
                else{
                    auto gsl_mat = to_gsl_matrix(matrix);

                    auto data = make_complex_packed_array(N);
                    gsl_fft_real_unpack(gsl_mat->data, data.get(), 1, N);

                    auto halfcomplex = make_unique_fft_halfcomplex_wavetable(N);
                    gsl_fft_halfcomplex_inverse(data.get(), 1, N, halfcomplex.get(), work.get());

                    auto result = make_gsl_matrix_complex(1, N);
                    for (size_t i = 0; i < N; ++i){
                        gsl_matrix_complex_set(result.get(), 0, i,
                                                gsl_complex{data.get()[2*i], data.get()[2*i+1]});
                    }
                    return MatrixExpression::construct(result);
                }
            }
            throw Exception("IFFT expected 1D Matrix. Got: ", matrix);
        }
    } ifft;
}
