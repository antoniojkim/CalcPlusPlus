#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <regex>

using namespace std;

typedef int (*func_t)(const std::string& str);

const std::regex token_regex("^(,|=|:=|<\\-|\\|\\||&&|\\||\\^\\||&|==|!=|<|>|<=|>=|~|<<|>>|\\+|\\-|\\*|/|%|//|!|\\^|\\*\\*|\\->|:|\\(|\\)|\\[|\\]|\\{|\\}|\\.|;|\\?|#|\\$|\\\"|\\'|\\\\|`|_|C|P)");
int regex_func(const std::string& str){
    if (!str.empty()){
        std::smatch match;
        if (std::regex_search(str, match, token_regex)){
            return regex_func(match.suffix()) + 1;
        }
    }
    return 0;
}

const std::string token_list[48] = {
    ",", "=", ":=", "<-", "|", "&&", "|", "^", "|", "&", "==", "!=", "<", ">", "<=", ">=", "~", "<<", ">>",
    "+", "-", "*", "/", "%", "//", "!", "^", "**", "->", ":", "(", ")", "[", "]", "{", "}",
    ".", ";", "?", "#", "$", "\"", "'", "\\", "`", "_", "C", "P"
};
int list_func(const std::string& str){
    if (!str.empty()){
        for (int i = 0; i < 48; ++i){
            if (strncmp(str.c_str(), token_list[i].c_str(), token_list[i].size()) == 0){
                return list_func(str.substr(token_list[i].size())) + 1;
            }
        }
    }
    return 0;
}

void timeit(func_t f, const std::string& str){
    std::clock_t start = std::clock();

    int numMatches = 0;
    for (int i = 0; i<100000; ++i){
        numMatches += f(str);
    }

    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    cout << "numMatches: " << numMatches << endl;
    cout << "duration:   " << duration << " seconds" << endl;

}

int main(){
    const std::string str = "\\^\\*\\*\\->:\\(\\)\\[\\]\\{\\}\\.;!=<><=>=~<<>>\\+\\-\\*/%//!\\?#\\$\\\"\\'\\\\`_CP,=:=<\\-\\\\|&&\\|\\^\\|&==";

    timeit(list_func, str);
    timeit(regex_func, str);
}

