
#include <cstdlib>
#include <sstream>
#include <ios>

#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

HexExpression::HexExpression(unsigned long long num): num{num} {}
HexExpression::HexExpression(const std::string& num) {
    char* endptr;
    this->num = strtoull(num.c_str()+2, &endptr, 16);
}

expression HexExpression::simplify() {
    return make_unique<HexExpression>(num);
}
expression HexExpression::derivative(const std::string& var) {
    return make_unique<HexExpression>(0);
}
expression HexExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: HexExpression::integrate");
}

bool HexExpression::evaluable(){ return true; }

double HexExpression::value() { return double(num); }

double HexExpression::value(const Variables& vars) { return double(num); }

bool HexExpression::isComplex(){ return false; }

expression HexExpression::copy() {
    return make_unique<HexExpression>(num);
}

std::ostream& HexExpression::print(std::ostream& out) {
    out << std::hex << num;
    return out;
}
std::ostream& HexExpression::postfix(std::ostream& out) {
    return print(out);
}
