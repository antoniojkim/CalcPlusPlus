#include "../Expression.h"
#include "../NumericalExpression.h"

double gsl_expression_function(double x, void* params){
    Variables vars;
    vars["x"] = NumExpression::construct(x);
    return ((Expression *) params)->value(vars);
}

gsl_function Expression::function() {
    gsl_function F;
    F.function = &gsl_expression_function;
    F.params = this;
    return F;
}


const Variables emptyVars;

expression Expression::evaluate() { return evaluate(emptyVars); }
expression Expression::evaluate(const Variables& vars) { return NumExpression::construct(this->complex(vars)); }

gsl_complex Expression::complex() const { return complex(emptyVars); }
gsl_complex Expression::complex(const Variables& vars) const { return gsl_complex{this->value(vars), 0}; }

double Expression::value() const { return value(emptyVars); }

expression Expression::copy(){ return shared_from_this(); }

bool Expression::prettyprint(std::ostream& out) const { return false; }

std::ostream& operator<<(std::ostream& out, const expression e){
    return e->print(out);
}
