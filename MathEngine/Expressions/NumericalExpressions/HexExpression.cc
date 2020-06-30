
#include <cstdlib>
#include <sstream>
#include <ios>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"

using namespace std;
using namespace Scanner;

HexExpression::HexExpression(unsigned long long num): NumericalExpression{HEX}, num{num} {}
HexExpression::HexExpression(const std::string& num): NumericalExpression{HEX} {
    char* endptr;
    this->num = strtoull(num.c_str()+2, &endptr, 16);
}

expression HexExpression::construct(unsigned long long num){
    return shared_ptr<HexExpression>(new HexExpression(num));
}
expression HexExpression::construct(const std::string& num){
    return shared_ptr<HexExpression>(new HexExpression(num));
}


bool HexExpression::isComplex() const { return false; }
bool HexExpression::isEvaluable(const Variables& vars) const { return true; }

expression HexExpression::eval(const Variables&) { return copy(); }
double HexExpression::value(const Variables& vars) const  { return double(num); }

bool HexExpression::equals(expression e, double precision) const {
    if (e == HEX){
        return num == e->value();
    }
    return false;
}

std::ostream& HexExpression::print(std::ostream& out, const bool pretty) const {
    out << "0x" << std::hex << num;
    return out;
}
std::ostream& HexExpression::postfix(std::ostream& out) const {
    return print(out, false);
}
