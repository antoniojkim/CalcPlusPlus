#include <iostream>
#include <cassert>
#include "str_func.h"

using namespace std;


int main(){
    const int i = str_func("ghi");
    assert( i == 2 );

    const int j = str_func("abcsdfg");
    assert( j == -1 );
}
