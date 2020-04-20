#include <iostream>
#include <cstdlib>
#include <memory>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>
#include <gsl/gsl_fft_complex.h>

using namespace std;

typedef std::unique_ptr<gsl_fft_real_workspace, decltype(&gsl_fft_real_workspace_free)> unique_fft_workspace;
unique_fft_workspace make_unique_fft_workspace(size_t n){
    return unique_fft_workspace(gsl_fft_real_workspace_alloc(n), gsl_fft_real_workspace_free);
}

typedef std::unique_ptr<gsl_fft_real_wavetable, decltype(&gsl_fft_real_wavetable_free)> unique_fft_real_wavetable;
unique_fft_real_wavetable make_unique_fft_real_wavetable(size_t n){
    return unique_fft_real_wavetable(gsl_fft_real_wavetable_alloc(n), gsl_fft_real_wavetable_free);
}
typedef std::unique_ptr<gsl_fft_complex_workspace, decltype(&gsl_fft_complex_workspace_free)> unique_fft_complex_workspace;
unique_fft_complex_workspace make_unique_fft_complex_workspace(size_t n){
    return unique_fft_complex_workspace(gsl_fft_complex_workspace_alloc(n), gsl_fft_complex_workspace_free);
}

typedef std::unique_ptr<gsl_fft_complex_wavetable, decltype(&gsl_fft_complex_wavetable_free)> unique_fft_complex_wavetable;
unique_fft_complex_wavetable make_unique_fft_complex_wavetable(size_t n){
    return unique_fft_complex_wavetable(gsl_fft_complex_wavetable_alloc(n), gsl_fft_complex_wavetable_free);
}

inline std::unieal.h>
#include <gsl/gsl_fft_cque_ptr<double[]> make_array(size_t n){
    return make_unique<double[]>(n);
}

inline std::unique_ptr<double[]> make_complex_packed_array(size_t n){
    return make_unique<double[]>(n * 2);
}

void real_data_fft(){
    const size_t N = 3;
    double data[N] = {9.83, 1.09, 4.8};
    // auto expected = std::vector<gsl_complex>{{15.72, 0.0}, {6.885, 3.212954248}, {6.885, -3.212954248}};

    cout << "data:  {";
    for (size_t i = 0; i < N; ++i){
        cout << data[i] << "  ";
    }
    cout << "}" << endl;
    cout << "Expected: {{15.72, 0.0}, {6.885, 3.212954248}, {6.885, -3.212954248}}" << endl;

    auto work = make_unique_fft_workspace(N);

    auto real = make_unique_fft_real_wavetable(N);
    gsl_fft_real_transform(data, 1, N, real.get(), work.get());

    auto complex = make_complex_packed_array(N);
    gsl_fft_halfcomplex_unpack(data, complex.get(), 1, N);

    cout << "complex:  {";
    for (size_t i = 0; i < N; ++i){
        cout << "{" << complex.get()[2 * i] << ", " << complex.get()[2 * i + 1] << "}" << "  ";
    }
    cout << "}" << endl;
}

void complex_data_fft(){

    const size_t N = 5;
    double data[N * 2] = {-7.27, 9.26, 8.28, -3.88, -7.17, 7.81, -7.06, 1.39, -0.95, -3.33};
    // auto expected = std::vector<gsl_complex>{{-14.17, 11.25}, {9.7579066345, -9.1245641453}, {-24.0264711221, 12.4060947822}, {-11.1683416753, 23.4658429731}, {3.256906163, 8.30262639}};

    cout << "data:  {";
    for (size_t i = 0; i < N; ++i){
        cout << "{" << data[2 * i] << ", " << data[2 * i + 1] << "}" << "  ";
    }
    cout << "}" << endl;
    cout << "Expected: {{-14.17, 11.25}, {9.7579066345, -9.1245641453}, {-24.0264711221, 12.4060947822}, {-11.1683416753, 23.4658429731}, {3.256906163, 8.30262639}}" << endl;

    auto work = make_unique_fft_complex_workspace(N);

    auto complextable = make_unique_fft_complex_wavetable(N);
    gsl_fft_complex_forward(data, 1, N, complextable.get(), work.get());

    cout << "data:  {";
    for (size_t i = 0; i < N; ++i){
        cout << "{" << data[2 * i] << ", " << data[2 * i + 1] << "}" << "  ";
    }
    cout << "}" << endl;
}


int main(){
    // real_data_fft();
    complex_data_fft();
}
