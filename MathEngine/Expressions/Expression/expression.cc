#include "../Expression.h"
#include "../NumericalExpression.h"

double gsl_expression_function(double x, void* params){
    Variables vars;
    vars["x"] = NumExpression::construct(x);
    return ((Expression *) params)->value(vars);
}

const Variables emptyVars;

expression Expression::evaluate(){ return evaluate(emptyVars); }
expression Expression::evaluate(const Variables& vars){ return NumExpression::construct(this->complex(vars)); }

gsl_complex Expression::complex(){ return complex(emptyVars); }
gsl_complex Expression::complex(const Variables& vars){ return gsl_complex{this->value(vars), 0}; }

double Expression::value(){ return value(emptyVars); }

bool Expression::prettyprint(std::ostream& out){ return false; }

std::ostream& operator<<(std::ostream& out, expression& e){
    return e->print(out);
}
