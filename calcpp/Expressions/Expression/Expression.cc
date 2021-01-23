
#include <algorithm>
#include <sstream>

#include "../Expression.h"
#include "../InvalidExpression.h"
#include "../NumericalExpression.h"

using namespace std;

namespace calcpp {

    const Environment defaultEnv;

    expression Expression::simplify() { return copy(); }
    expression Expression::derivative(const std::string& var) {
        THROW_ERROR("Invalid differentiation: " << copy());
    }
    expression Expression::integrate(const std::string& var) {
        THROW_ERROR("Invalid Integration: " << copy());
    }

    expression Expression::eval(const Environment& env) {
        if (this->is(Type::COMPLEX)) {
            return NumExpression::construct(this->complex(env));
        } else {
            return NumExpression::construct(this->value(env));
        }
    }
    gsl_complex Expression::complex(const Environment& env) const {
        return gsl_complex{this->value(env), 0};
    }

    std::vector<double> Expression::array() {
        if (size() == 0) {
            THROW_VALUE_ERROR("Cannot construct array from: " << copy());
        }
        std::vector<double> array;
        array.reserve(size());

        for (size_t i = 0; i < size(); ++i) { array.emplace_back(at(i)->value()); }
        return array;
    }
    expression Expression::at(const int index) {
        if (index == 0) { return copy(); }
        THROW_ERROR("Array Index Out of Bounds (index: " << index << "): " << copy());
    }
    Double Expression::get(const int index) { return at(index)->value(); }
    size_t Expression::shape(const int axis) const {
        if (axis == 0) { return size(); }
        THROW_ERROR("Axis out of bounds: " << axis);
    }
    size_t Expression::size() const { return 1; }

    expression Expression::call(expression e) {
        THROW_ERROR("Expression is not callable: " << copy());
    }
    expression Expression::apply(TransformerFunction f) {
        THROW_ERROR("Cannot apply function to Expression: " << copy());
    }

    unsigned int Expression::id() const { return (unsigned int) this; }

    expression Expression::copy() { return shared_from_this(); }

    std::ostream& operator<<(std::ostream& out, const expression e) {
        return e->str(out);
    }

#define OSTREAM_WRAPPER_IMPL(name)                                                     \
    std::ostream& operator<<(                                                          \
        std::ostream& out, const Expression::expression_##name& obj) {                 \
        return obj.e->name(out);                                                       \
    }                                                                                  \
    Expression::expression_##name Expression::name() {                                 \
        return Expression::expression_ #name{copy()};                                  \
    }

    OSTREAM_WRAPPER_IMPL(repr);
    OSTREAM_WRAPPER_IMPL(str);
    OSTREAM_WRAPPER_IMPL(postfix);

}  // namespace calcpp
