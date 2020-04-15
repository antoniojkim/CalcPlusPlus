#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int main(){
    char array[5] = {'a', 'b', 'c', 'd', 'e'};

    string_view sv1 (array, 5);

    cout << sv1 << endl;

    array[2] = '3';

    cout << sv1 << endl;
}
