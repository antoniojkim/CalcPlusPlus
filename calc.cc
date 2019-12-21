
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

#include <gsl/gsl_poly.h>
#include "Parser/Scanner/scanner.h"
#include "Parser/Parser/parser.h"

int main(int argc, char** argv){
    // Parser parser;
    // string s;
    // while (getline(cin, s)){
    //     // cout << s << endl;
    //     list<Token> tokens;
    //     scan(s, tokens);
    //     print(cout, tokens, " ") << endl;
    // }

    string s = "cossinh3+5i-arcsin(x,4)+6integrate(sinx, 4, 5)^|4";

    list<Token> tokens;
    if (scan(s, tokens)){
        print(cout, tokens, " ") << endl;
    }
}
