
#include <bitset>
#include <cstdlib>
#include <sstream>

#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../../Utils/exceptions.h"

using namespace std;

BinExpression::BinExpression(unsigned long long num): num{num} {}
BinExpression::BinExpression(const std::string& num) {
    char* endptr;
    this->num = strtoull(num.c_str()+2, &endptr, 2);
}

expression BinExpression::construct(unsigned long long num){
    return shared_ptr<BinExpression>(new BinExpression(num));
}
expression BinExpression::construct(const std::string& num){
    return shared_ptr<BinExpression>(new BinExpression(num));
}

expression BinExpression::simplify() { return copy(); }
expression BinExpression::derivative(const std::string& var) {
    return BinExpression::construct(0);
}
expression BinExpression::integrate(const std::string& var) {
    return InvalidExpression::construct(Exception("Unimplemented Error: BinExpression::integrate"));
}

bool BinExpression::evaluable() const { return true; }

expression BinExpression::evaluate(const Variables&) { return copy(); }

double BinExpression::value(const Variables& vars) const { return double(num); }

bool BinExpression::isComplex() const { return false; }

std::ostream& BinExpression::print(std::ostream& out) const {
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
    return print(out);
}
