
#include <sstream>
#include <utility>

#include "../../Functions/Functions.h"
#include "../FunctionExpression.h"

using namespace std;

namespace calcpp {

    FunctionExpression::FunctionExpression(
        const std::string& name, std::initializer_list<expression> signature) :
        name{name}, signature{signature} {
        int stage = 0;
        for (auto s : signature) {
            if (s == Type::VAR) {
                if (stage != 0) {
                    THROW_ERROR(
                        "Positional argument cannot follow vararg or keyword arg in "
                        "signature");
                }
            } else if (s == Type::VARARG) {
                switch (stage) {
                    case 1:
                        THROW_ERROR("Signature cannot contain multiple varargs");
                    case 2:
                        THROW_ERROR("vararg cannot follow keyward arg in signature");
                    default:
                        stage = 1;
                        break;
                }
            } else if (s == Type::ASSIGNMENT) {
                stage = 2;
            }
        }
    }

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
