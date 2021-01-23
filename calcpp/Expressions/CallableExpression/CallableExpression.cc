
#include "../CallableExpression.h"

using namespace std;

namespace calcpp {

    CallableExpression::CallableExpression(expression f, expression arg) :
        f{f}, arg{arg} {}

    expression CallableExpression::construct(expression f, expression arg) {
        return shared_ptr<CallableExpression>(new CallableExpression(f, arg));
    }

    expression CallableExpression::at(const int index) {
        switch (index) {
            case 0:
                return f;
            case 1:
                return arg;
            default:
                THROW_ERROR("CallableExpression::at Invalid index: " << index);
        }
    }

    expression CallableExpression::eval(const Environment& env) {
        return f(arg->eval(env));
    }
    long double CallableExpression::value(const Environment& env) const {
        return f(arg->eval(env))->value();
    }

    bool CallableExpression::equals(expression e, double precision) const {
        return e->is(Type::CALLABLE) && f->equals(e->at(0), precision) &&
               arg->equals(e->at(1), precision);
    }
    bool CallableExpression::is(Type type, const Environment& env) const {
        switch (type) {
            case Type::EVALUABLE:
                return arg->is(type, env);
            case Type::CALLABLE:
                return true;
            default:
                return false;
        }
    }

    std::ostream& CallableExpression::repr(std::ostream& out) const {
        return out << "call(" << f->repr() << ", " << arg->repr() << ")";
    }
    std::ostream& CallableExpression::str(std::ostream& out) const {
        if (arg->is(Type::TUPLE)) {
            return out << f->repr() << arg->str();
        } else {
            return out << f->repr() << "(" << arg->str() << ")";
        }
    }
    std::ostream& CallableExpression::postfix(std::ostream& out) const {
        return out << arg->postfix() << " " << f->repr();
    }

}  // namespace calcpp
