#pragma once

#include <list>
#include <vector>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_complex.h>

#include "../../Expression.h"
#include "../../TupleExpression.h"
#include "../../MatrixExpression.h"

using namespace std;


typedef std::unique_ptr<gsl_fft_real_workspace, decltype(&gsl_fft_real_workspace_free)> unique_fft_workspace;
unique_fft_workspace make_unique_fft_workspace(size_t n){
    return unique_fft_workspace(gsl_fft_real_workspace_alloc(n), gsl_fft_real_workspace_free);
}

typedef std::unique_ptr<gsl_fft_real_wavetable, decltype(&gsl_fft_real_wavetable_free)> unique_fft_real_wavetable;
unique_fft_real_wavetable make_unique_fft_real_wavetable(size_t n){
    return unique_fft_real_wavetable(gsl_fft_real_wavetable_alloc(n), gsl_fft_real_wavetable_free);
}

typedef std::unique_ptr<gsl_fft_halfcomplex_wavetable, decltype(&gsl_fft_halfcomplex_wavetable_free)> unique_fft_halfcomplex_wavetable;
unique_fft_halfcomplex_wavetable make_unique_fft_halfcomplex_wavetable(size_t n){
    return unique_fft_halfcomplex_wavetable(gsl_fft_halfcomplex_wavetable_alloc(n), gsl_fft_halfcomplex_wavetable_free);
}

typedef std::unique_ptr<gsl_fft_complex_workspace, decltype(&gsl_fft_complex_workspace_free)> unique_fft_complex_workspace;
unique_fft_complex_workspace make_unique_fft_complex_workspace(size_t n){
    return unique_fft_complex_workspace(gsl_fft_complex_workspace_alloc(n), gsl_fft_complex_workspace_free);
}

typedef std::unique_ptr<gsl_fft_complex_wavetable, decltype(&gsl_fft_complex_wavetable_free)> unique_fft_complex_wavetable;
unique_fft_complex_wavetable make_unique_fft_complex_wavetable(size_t n){
    return unique_fft_complex_wavetable(gsl_fft_complex_wavetable_alloc(n), gsl_fft_complex_wavetable_free);
}

inline std::unique_ptr<double[]> make_complex_packed_array(size_t n){
    return make_unique<double[]>(n * 2);
}

expression fft(MatrixExpression* matrix){
    if (matrix && (matrix->rows() == 1 || matrix->cols() == 1)){
        size_t N = matrix->rows() * matrix->cols();
        auto work = make_unique_fft_workspace(N);
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
            return make_unique<MatrixExpression>(result.get());
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
            return make_unique<MatrixExpression>(result.get());
        }
    }
}

expression fe_fft(list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        auto expr = args.front()->evaluate(vars);
        return fft(expr->matrix());
    }
    else{
        list<expression> exprs;
        for (auto& arg : args){
            exprs.emplace_back(arg->evaluate(vars));
        }
        auto expr = make_unique<MatrixExpression>(std::move(exprs), 1, args.size());
        return fft(expr->matrix());
    }
}

expression ifft(MatrixExpression* matrix){
    if (matrix && (matrix->rows() == 1 || matrix->cols() == 1)){
        size_t N = matrix->rows() * matrix->cols();
        auto work = make_unique_fft_workspace(N);
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
            return make_unique<MatrixExpression>(result.get());
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
            return make_unique<MatrixExpression>(result.get());
        }
    }
}

expression fe_ifft(list<expression>& args, const Variables& vars){
    if (args.size() == 1){
        auto expr = args.front()->evaluate(vars);
        return ifft(expr->matrix());
    }
    else{
        list<expression> exprs;
        for (auto& arg : args){
            exprs.emplace_back(arg->evaluate(vars));
        }
        auto expr = make_unique<MatrixExpression>(std::move(exprs), 1, args.size());
        return ifft(expr->matrix());
    }
}
