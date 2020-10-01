#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

template<typename RET, typename... Args>
void timeit(int iterations, RET (*f)(Args...), Args&&... args){
    std::clock_t start = std::clock();

    for (int i = 0; i<iterations; ++i){
        f(args...);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "iterations: " << iterations << std::endl;
    if (duration > 1){
        std::cout << "time: " << duration << " seconds" << std::endl;
    }
    else {
        std::cout << "time: " << duration * 1000.0 << " milliseconds" << std::endl;
    }
    double sec_per_iter = duration / iterations;
    if (sec_per_iter > 1){
        std::cout << duration / iterations << " seconds per iteration" << std::endl;
    }
    else{
        std::cout << duration / iterations * 1000 << " milliseconds per iteration" << std::endl;
    }
}
