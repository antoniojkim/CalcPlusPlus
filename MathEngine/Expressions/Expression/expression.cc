#include "../Expression.h"
#include "../NumericalExpression.h"

double gsl_expression_function(double x, void* params){
    Variables vars;
    vars["x"] = std::make_unique<NumExpression>(x);
    return ((Expression *) params)->value(vars);
}

expression Expression::evaluate(){ return std::make_unique<NumExpression>(this->complex()); }
expression Expression::evaluate(const Variables& vars){ return std::make_unique<NumExpression>(this->complex(vars)); }

gsl_complex Expression::complex(){ return gsl_complex{this->value(), 0}; }
gsl_complex Expression::complex(const Variables& vars){ return gsl_complex{this->value(vars), 0}; }

std::ostream& operator<<(std::ostream& out, expression& e){
    return e->print(out);
}
