#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>

#include <Scanner/scanner.h>
#include <Parser/modifiedShuntingYard.h>

using namespace std;
using namespace Scanner;

int main(){
    list<Token> tokens;
    if (!scan("5+x*5+ mean(7*7, 8*(8+x), 9/9)+{{sin(3), -2}, {3!, cos4}} + rand()", tokens)){
        throw std::runtime_error("Unable to scan");
    }

    cout << "Tokens:  ";
    for (auto& t : tokens){
        cout << t.lexeme << " ";
    }
    cout << endl << endl;

    ModifiedShuntingYard parser;
    parser.parse(tokens);
}
