
#include <sstream>

#include "../Expression.h"
#include "../NumericalExpression.h"
#include "../InvalidExpression.h"

using namespace std;


const Variables emptyVars;


Expression::Expression(Scanner::Type kind): kind{kind} {}
Expression::~Expression() = default;

expression Expression::simplify(){ return copy(); }
expression Expression::derivative(const std::string& var) {
    throw Exception("Invalid differentiation: ", copy());
}
expression Expression::integrate(const std::string& var){
    throw Exception("Invalid Integration: ", copy());
}

expression Expression::eval(const Variables& vars) { return NumExpression::construct(this->complex(vars)); }
gsl_complex Expression::complex(const Variables& vars) const { return gsl_complex{this->value(vars), 0}; }

std::vector<double> Expression::array(){
    if (size() == 0){
        throw Exception("Cannot construct array from: ", copy());
    }
    std::vector<double> array;
    array.reserve(size());

    for (size_t i = 0; i < size(); ++i){
        array.emplace_back(at(i)->value());
    }
    return array;
}
expression Expression::at(const int index){
    if (index == 0){
        return copy();
    }
    throw Exception("Array Index Out of Bounds (index: ", index, "): ", copy());
}
double Expression::get(const int index){
    return at(index)->value();
}
size_t Expression::shape(const int axis) const {
    if (axis == 0){
        return size();
    }
    throw Exception("Axis out of bounds: ", axis);
}
size_t Expression::size() const { return 1; }

expression Expression::call(expression e){
    throw Exception("Expression is not callable: ", copy());
}

std::string Expression::repr() const {
    ostringstream oss;
    oss << this;
    return oss.str();
}
int Expression::id() const { return (int) kind; }

expression Expression::copy(){ return shared_from_this(); }

std::ostream& operator<<(std::ostream& out, const expression e){
    return e->print(out);
}
