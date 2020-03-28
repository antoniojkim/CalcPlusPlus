#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstring>
#include <regex>

using namespace std;

typedef int (*func_t)(const std::string& str);

static const std::regex HEX_regex ("^(0x[0-9a-fA-F]+)");
int regex_func(const std::string& str){
    if (!str.empty()){
        std::smatch match;
        if (std::regex_search(str, match, HEX_regex)){
            return regex_func(match.suffix()) + 1;
        }
    }
    return 0;
}

int cpp_func(const std::string& str){
    if (str.size() > 2 && str[0] == '0' && str[1] == 'x'){
        for (unsigned int i = 2; i < str.size(); ++i){
            if (!isxdigit(str[i])){
                if (i == 2) return 0;
                return cpp_func(str.substr(i)) + 1;
            }
        }
        return 1;
    }
    return 0;
}

void timeit(func_t f, const std::string& str){
    std::clock_t start = std::clock();

    int numMatches = 0;
    for (int i = 0; i<1000000; ++i){
        numMatches += f(str);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "numMatches: " << numMatches << endl;
    cout << "duration:   " << duration << " seconds" << endl;

}

int main(){
    const std::string str = "x283746af9876439817236498127634981276349182764981273649821abcd736ef4d1e9fe8237469182736";

    timeit(regex_func, str);
    timeit(cpp_func, str);
}

