#include "../Expression.h"
#include "../NumericalExpression.h"

using namespace std;

Expression::gsl_expression_struct::gsl_expression_struct(Expression* e, const std::string var): e{e}, var{var} {}
double Expression::gsl_expression_function(double x, void* p) {
    gsl_expression_struct* params = (gsl_expression_struct*) p;
    params->vars[params->var] = NumExpression::construct(x);
    return params->e->value(params->vars);
}

gsl_function Expression::function(const std::string& var) {
    gsl_params = make_unique<Expression::gsl_expression_struct>(this, var);
    gsl_function F;
    F.function = &Expression::gsl_expression_function;
    F.params = gsl_params.get();
    return F;
}

Expression::~Expression() = default;

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
