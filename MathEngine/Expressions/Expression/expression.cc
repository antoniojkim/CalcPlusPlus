#include "../Expression.h"
#include "../NumericalExpression.h"

double gsl_expression_function(double x, void* params){
    Variables vars;
    vars["x"] = std::make_unique<NumExpression>(x);
    return ((Expression *) params)->value(vars);
}

expression Expression::evaluate(){ return std::make_unique<NumExpression>(this->value()); }
expression Expression::evaluate(const Variables& vars){ return std::make_unique<NumExpression>(this->value(vars)); }

std::ostream& operator<<(std::ostream& out, expression& e){
    return out << e.get();
}

std::ostream& operator<<(std::ostream& out, Expression* e){
    return e->print(out);
}
