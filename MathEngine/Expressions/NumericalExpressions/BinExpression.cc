
#include <bitset>
#include <cstdlib>
#include <sstream>

#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

BinExpression::BinExpression(unsigned long long num): num{num} {}
BinExpression::BinExpression(const std::string& num) {
    char* endptr;
    this->num = strtoull(num.c_str()+2, &endptr, 2);
}

expression BinExpression::construct(unsigned long long num){
    return unique_ptr<BinExpression>(new BinExpression(num));
}
expression BinExpression::construct(const std::string& num){
    return unique_ptr<BinExpression>(new BinExpression(num));
}

expression BinExpression::simplify() {
    return BinExpression::construct(num);
}
expression BinExpression::derivative(const std::string& var) {
    return BinExpression::construct(0);
}
expression BinExpression::integrate(const std::string& var) {
    throw Exception("Unimplemented Error: BinExpression::integrate");
}

bool BinExpression::evaluable(){ return true; }


double BinExpression::value(const Variables& vars) { return double(num); }

bool BinExpression::isComplex(){ return false; }

expression BinExpression::copy() {
    return BinExpression::construct(num);
}

std::ostream& BinExpression::print(std::ostream& out) {
    out << "0b" << std::bitset<sizeof(unsigned long long)>(num);
    return out;
}
std::ostream& BinExpression::postfix(std::ostream& out) {
    return print(out);
}
