
#include <cstdlib>
#include <ios>
#include <sstream>

#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../ExpressionOperations.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"

using namespace std;

namespace calcpp {

    HexExpression::HexExpression(unsigned long long num) : num{num} {}

    expression HexExpression::construct(unsigned long long num) {
        return shared_ptr<HexExpression>(new HexExpression(num));
    }

    constexpr const FType HexType = Type::HEX | Type::EVALUABLE;

    bool HexExpression::is(const Type type, const Environment& env) {
        return (HexType & type) != 0;
    }
    bool HexExpression::equals(expression e, double precision) const {
        if (e == Type::HEX) { return num == (unsigned long long) e->value(); }
        return false;
    }

    expression HexExpression::eval(const Environment& env) { return copy(); }
    double HexExpression::value(const Environment& env) const { return double(num); }

    std::ostream& HexExpression::repr(std::ostream& out) const { return print(out); }
    std::ostream& HexExpression::print(std::ostream& out) const {
        return out << "0x" << std::hex << num;
    }
    std::ostream& HexExpression::postfix(std::ostream& out) const { return print(out); }

}  // namespace calcpp
