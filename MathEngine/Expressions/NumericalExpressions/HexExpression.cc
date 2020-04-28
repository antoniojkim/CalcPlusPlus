
#include <cstdlib>
#include <sstream>
#include <ios>

#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

HexExpression::HexExpression(unsigned long long num): num{num} {}
HexExpression::HexExpression(const std::string& num) {
    char* endptr;
    this->num = strtoull(num.c_str()+2, &endptr, 16);
}

expression HexExpression::construct(unsigned long long num){
    return shared_ptr<HexExpression>(new HexExpression(num));
}
expression HexExpression::construct(const std::string& num){
    return shared_ptr<HexExpression>(new HexExpression(num));
}

expression HexExpression::simplify() { return copy(); }
expression HexExpression::derivative(const std::string& var) {
    return HexExpression::construct(0);
}
expression HexExpression::integrate(const std::string& var) {
    return InvalidExpression::construct(Exception("Unimplemented Error: HexExpression::integrate"));
}

bool HexExpression::evaluable() const { return true; }

expression HexExpression::evaluate(const Variables&) { return copy(); }

double HexExpression::value(const Variables& vars) const  { return double(num); }

bool HexExpression::isComplex() const { return false; }

std::ostream& HexExpression::print(std::ostream& out) const {
    out << "0x" << std::hex << num;
    return out;
}
std::ostream& HexExpression::postfix(std::ostream& out) const {
    return print(out);
}
