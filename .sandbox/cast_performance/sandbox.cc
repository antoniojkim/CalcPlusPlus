#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct B;

struct A {
    A(){}
    virtual ~A(){}
    virtual B* getB(){ return nullptr; }
};

struct B: public A {
    B(){}
    ~B(){}
    B* getB() override { return this; }
};

size_t casting(A** a, size_t size){
    size_t numB = 0;
    for (size_t i = 0; i < size; ++i){
        if (dynamic_cast<B*>(a[i])){
            ++numB;
        }
    }
    return numB;
}

size_t virtualOverride(A** a, size_t size){
    size_t numB = 0;
    for (size_t i = 0; i < size; ++i){
        if (a[i]->getB()){
            ++numB;
        }
    }
    return numB;
}

typedef size_t (*func_t)(A** a, size_t size);

void timeit(func_t f, A** a, size_t size){
    std::clock_t start = std::clock();

    size_t isum = 0;
    for (int i = 0; i<100000; ++i){
        isum += f(a, size);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "isum: " << isum << endl;
    cout << "duration: " << duration << " seconds" << endl;

}

int main(){
    srand(time(NULL));
    const size_t N = 10000;
    A* a[N];
    for (size_t i = 0; i < N; ++i){
        if (rand() % 2 == 0){
            a[i] = new A();
        }
        else{
            a[i] = new B();
        }
    }

    timeit(casting, a, N);
    timeit(virtualOverride, a, N);

    for (size_t i = 0; i < N; ++i){
        delete a[i];
    }
}

