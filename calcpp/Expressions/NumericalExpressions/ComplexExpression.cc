
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

    ComplexExpression::ComplexExpression(const Double real, const Double imag) :
        real{real}, imag{imag} {}

    expression ComplexExpression::construct(const Double real, const Double imag) {
        return shared_ptr<ComplexExpression>(new ComplexExpression(real, imag));
    }
    expression ComplexExpression::construct(const gsl_complex& z) {
        return shared_ptr<ComplexExpression>(
            new ComplexExpression(GSL_REAL(z), GSL_IMAG(z)));
    }

    Double ComplexExpression::get(const int index) {
        switch (index) {
            case 0:
                return real;
            case 1:
                return imag;
            default:
                THROW_ERROR("ComplexExpression::get Invalid Index: " << index);
        }
    }

    bool ComplexExpression::is(const Type type, const Environment& env) const {
        switch (type) {
            case Type::COMPLEX:
                return true;
            case Type::EVALUABLE:
                return !IS_NAN(real) && !IS_NAN(imag);
            default:
                return false;
        }
    }

    expression ComplexExpression::eval(const Environment& env) {
        if (is(Type::EVALUABLE, env)) { return copy(); }
        THROW_ERROR("Invalid Complex Number: " << copy());
    }
    Double ComplexExpression::value(const Environment& env) const { return val; }
    // gsl_complex ComplexExpression::complex(const Environment& env) const {
    //     return gsl_complex{real, imag};
    // }

    bool ComplexExpression::equals(expression e, const double precision) const {
        if (e == Type::COMPLEX) {
            return compare(complex(), e->complex(), precision) == 0;
        }
        return false;
    }

    std::ostream& ComplexExpression::repr(std::ostream& out) const {
        return out << "Complex(" << real << ", " << imag << ")";
    }
    std::ostream& ComplexExpression::print(std::ostream& out) const {
        if (!is(Type::EVALUABLE)) { return out << "NaN"; }
        if (real == 0 && imag == 0) { return out << "0"; }
        if (real != 0) {
            out << std::setprecision(16) << real;
            if (imag > 0) { out << "+"; }
        }
        if (imag != 0) { out << std::setprecision(16) << imag << "i"; }
        return out;
    }

    std::ostream& ComplexExpression::postfix(std::ostream& out) const {
        if (real != 0) {
            out << std::setprecision(16) << real;
            if (imag > 0) {
                out << " " << std::setprecision(16) << imag << "i"
                    << " +";
            } else if (imag < 0) {
                out << " " << std::setprecision(16) << -imag << "i"
                    << " -";
            }
        } else if (imag != 0) {
            out << std::setprecision(16) << imag << "i";
        } else {
            out << 0;
        }
        return out;
    }

}  // namespace calcpp
