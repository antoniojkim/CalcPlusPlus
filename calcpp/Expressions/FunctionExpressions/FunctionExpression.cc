
#include <sstream>
#include <utility>

#include "../../Functions/Functions.h"
#include "../FunctionExpression.h"

using namespace std;

namespace calcpp {

    FunctionExpression::FunctionExpression(
        const std::string& name, std::initializer_list<expression> signature) :
        name{name}, signature{signature} {}

    expression FunctionExpression::at(const int index) { return signature.at(index); }
    size_t size() { return signature.size(); }

    bool FunctionExpression::is(const Type type, const Environment& env) {
        return type == Type::Function;
    }

    bool FunctionExpression::equals(expression e, double precision) const {
        if (e == Type::FUNCTION) { return id() == e->id(); }
        return false;
    }

    std::ostream& FunctionExpression::repr(std::ostream& out) const {
        return out << name;
    }
    std::ostream& FunctionExpression::print(std::ostream& out) const {
        return repr(out);
    }
    std::ostream& FunctionExpression::postfix(std::ostream& out) const {
        return repr(out);
    }

}  // namespace calcpp
