
#include <cstdlib>
#include <sstream>
#include <ios>

#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

HexExpression::HexExpression(unsigned long long num): Expression{HEX}, num{num} {}
HexExpression::HexExpression(const std::string& num): Expression{HEX} {
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
bool HexExpression::isEvaluable() const { return true; }

expression HexExpression::eval(const Variables&) { return copy(); }
double HexExpression::value(const Variables& vars) const  { return double(num); }

bool HexExpression::equals(expression e, double precision) const {
    if (e->hex()){
        return num == e->hex()->num;
    }
    return false;
}

std::ostream& HexExpression::print(std::ostream& out, const bool pretty) const {
    out << "0x" << std::hex << num;
    return out;
}
std::ostream& HexExpression::postfix(std::ostream& out) const {
    return print(out);
}
