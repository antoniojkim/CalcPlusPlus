#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std;

struct B;

struct A: public std::enable_shared_from_this<A> {
    A(){}
    virtual ~A(){}
    shared_ptr<B> sharedB(){ return dynamic_pointer_cast<B>(shared_from_this()); }
    virtual B* getB(){ return nullptr; }
};

struct B: public A {
    B(){}
    ~B(){}
    B* getB() override { return this; }
};

size_t casting(shared_ptr<A>* a, size_t size){
    size_t numB = 0;
    for (size_t i = 0; i < size; ++i){
        if (dynamic_cast<B*>(a[i].get())){
            ++numB;
        }
    }
    return numB;
}

size_t virtualOverride(shared_ptr<A>* a, size_t size){
    size_t numB = 0;
    for (size_t i = 0; i < size; ++i){
        if (a[i]->getB()){
            ++numB;
        }
    }
    return numB;
}

size_t sharedFromThis(shared_ptr<A>* a, size_t size){
    size_t numB = 0;
    for (size_t i = 0; i < size; ++i){
        if (a[i]->sharedB()){
            ++numB;
        }
    }
    return numB;
}

typedef size_t (*func_t)(shared_ptr<A>* a, size_t size);

void timeit(func_t f, shared_ptr<A>* a, size_t size){
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
    shared_ptr<A> a[N];
    for (size_t i = 0; i < N; ++i){
        if (rand() % 2 == 0){
            a[i] = make_shared<A>();
        }
        else{
            a[i] = make_shared<B>();
        }
    }

    timeit(casting, a, N);
    timeit(virtualOverride, a, N);
    timeit(sharedFromThis, a, N);
}
