
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

#include "../../Utils/Exception.h"
#include "../../Utils/Fraction.h"
#include "../../Utils/Numeric.h"
#include "../ExpressionOperations.h"
#include "../NumericalExpression.h"
#include "../VariableExpression.h"

using namespace std;

namespace calcpp {

    NumExpression::NumExpression(Double val) : val{val} {}

    expression NumExpression::construct(Double val) {
        return shared_ptr<NumExpression>(new NumExpression(val));
    }

    bool NumExpression::is(const Type type, const Environment& env) const {
        switch (type) {
            case Type::NUM:
                return true;
            case Type::EVALUABLE:
                return !IS_NAN(val);
            default:
                return false;
        }
    }

    bool NumExpression::equals(expression e, const double precision) const {
        return e == Type::NUM && compare(val, e->value(), precision);
    }

    expression NumExpression::eval(const Environment& env) {
        if (!IS_NAN(val)) { return copy(); }
        THROW_ERROR("Invalid Number: " << copy());
    }
    Double NumExpression::value(const Environment& env) const { return (Double) val; }

    std::ostream& NumExpression::repr(std::ostream& out) const {
        return out << "Num(" << val << ")";
    }
    std::ostream& NumExpression::print(std::ostream& out) const {
        if (IS_NAN(val)) { return out << "NaN"; }
        return out << std::setprecision(16) << val;
    }

    std::ostream& NumExpression::postfix(std::ostream& out) const { return print(out); }

}  // namespace calcpp
