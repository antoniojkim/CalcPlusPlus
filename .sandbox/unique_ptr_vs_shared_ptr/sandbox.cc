#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

constexpr const int classSize = 2;

class A {
    double value;
    double values[classSize];

    public:
        A(double value): value{value} {
            for (int i = 0; i < classSize; ++i){
                values[i] = (value + i) / 1e3 - i;
            }
        }

        double sum(){
            double total = 0;
            for (int i = 0; i < classSize; ++i){
                total += values[i];
            }
            return total;
        }

        unique_ptr<A> copy(){
            return make_unique<A>(value);
        }
};

double timeA(){
    double total = 0;
    for (int i = 0; i < 10000; ++i){
        auto a = std::unique_ptr<A>(new A(i));
        for (int j = 0; j < 10000; ++j){
            auto aj = a->copy();
            total += aj->sum();
        }
    }
    return total;
}

class B: public std::enable_shared_from_this<B> {
    double value;
    double values[classSize];

    public:
        B(double value): value{value} {
            for (int i = 0; i < classSize; ++i){
                values[i] = (value + i) / 1e3 - i;
            }
        }

        double sum(){
            double total = 0;
            for (int i = 0; i < classSize; ++i){
                total += values[i];
            }
            return total;
        }

        shared_ptr<B> copy(){
            return shared_from_this();
        }
};

double timeB(){
    double total = 0;
    for (int i = 0; i < 10000; ++i){
        auto b = std::make_shared<B>(i);
        for (int j = 0; j < 10000; ++j){
            auto bc = b->copy();
            total += bc->sum();
        }
    }
    return total;
}

typedef double (*func_t)();

void timeit(func_t f){
    std::clock_t start = std::clock();

    double total = 0;
    for (int i = 0; i<10; ++i){
        total += f();
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "total: " << total << endl;
    cout << "duration: " << duration << " seconds" << endl << endl;

}

int main(){
    timeit(timeA);
    timeit(timeB);
    timeit(timeA);
    timeit(timeB);
}
