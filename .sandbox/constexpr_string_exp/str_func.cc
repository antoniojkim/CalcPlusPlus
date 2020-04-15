#include <cstring>

using namespace std;

constexpr const char* array[3] = {"abc", "def", "ghi"};

constexpr int str_func(const char * str){
    for (int i = 0; i < 3; ++i){
        if (strcmp(str, array[i]) == 0){
            return i;
        }
    }
    return -1;
}
