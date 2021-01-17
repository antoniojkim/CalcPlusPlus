
#include <bitset>
#include <cstdlib>
#include <sstream>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../VariableExpression.h"

using namespace std;
using namespace Scanner;

BinExpression::BinExpression(unsigned long long num): NumericalExpression{BIN}, num{num} {}
BinExpression::BinExpression(const std::string& num): NumericalExpression{BIN} {
    char* endptr;
    this->num = strtoull(num.c_str()+2, &endptr, 2);
}

expression BinExpression::construct(unsigned long long num){
    return shared_ptr<BinExpression>(new BinExpression(num));
}
expression BinExpression::construct(const std::string& num){
    return shared_ptr<BinExpression>(new BinExpression(num));
}


bool BinExpression::isComplex() const { return false; }
bool BinExpression::isEvaluable(const Variables& vars) const { return true; }

expression BinExpression::eval(const Variables& vars) { return copy(); }
double BinExpression::value(const Variables& vars) const { return double(num); }

bool BinExpression::equals(expression e, double precision) const {
    if (e == BIN){
        return num == e->value();
    }
    return false;
}

std::ostream& BinExpression::print(std::ostream& out, const bool pretty) const {
    unsigned long long n = num;
    char buffer[128];
    int i = 0;
    while (n > 0){
        if (i >= 128){
            throw Exception("Buffer too short.");
        }
        buffer[i++] = ((n & 0b1) == 1) ? '1' : '0';
        n >>= 1;
    }
    out << "0b";
    while(i > 0){
        out << buffer[--i];
    }
    return out;
}
std::ostream& BinExpression::postfix(std::ostream& out) const {
    return print(out, false);
}
