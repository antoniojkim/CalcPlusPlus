
#include <bitset>
#include <cstdlib>
#include <sstream>

#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"
#include "../VariableExpression.h"

using namespace std;

namespace calcpp {

    BinExpression::BinExpression(unsigned long long num) : num{num} {}

    expression BinExpression::construct(unsigned long long num) {
        return shared_ptr<BinExpression>(new BinExpression(num));
    }

    expression BinExpression::eval(const Environment& env) { return copy(); }
    double BinExpression::value(const Environment& env) const { return double(num); }

    constexpr const FType BinType = Type::BIN | Type::EVALUABLE;

    bool BinExpression::is(const Type type, const Environment& env) const {
        return (type & BinType) != 0;
    }
    bool BinExpression::equals(expression e, double precision) const {
        if (e == Type::BIN) { return num == e->value(); }
        return false;
    }

    std::ostream& BinExpression::repr(std::ostream& out) const {
        return out << "Bin(" << num << ")";
    }
    std::ostream& BinExpression::print(std::ostream& out) const {
        unsigned long long n = num;
        char buffer[129];
        int i = 0;
        while (n > 0) {
            if (i >= 128) { throw Exception("Buffer too short."); }
            buffer[i++] = ((n & 0b1) == 1) ? '1' : '0';
            n >>= 1;
        }
        buffer[i] = '\0';
        return out << "0b" << buffer;
    }
    std::ostream& BinExpression::postfix(std::ostream& out) const { return print(out); }

}  // namespace calcpp
