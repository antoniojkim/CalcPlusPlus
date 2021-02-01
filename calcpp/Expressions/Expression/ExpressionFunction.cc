#include "../Expression.h"
#include "../ExpressionOperations.h"
#include "../NumericalExpression.h"

using namespace std;

namespace calcpp {

    Expression::gsl_expression_struct::gsl_expression_struct(
        Expression* e, const expression var) :
        e{e}, var{var} {}

    double Expression::gsl_expression_function(double x, void* p) {
        gsl_expression_struct* params = (gsl_expression_struct*) p;
        params->env.set(params->var, num(x));
        return params->e->value(params->env);
    }

    gsl_function Expression::function(const expression var) {
        if (var != Type::VAR) {
            THROW_ERROR("Cannot construct expression function with var: " << var)
        }
        gsl_params = make_unique<Expression::gsl_expression_struct>(this, var);
        gsl_function F;
        F.function = &Expression::gsl_expression_function;
        F.params = gsl_params.get();
        return F;
    }

}  // namespace calcpp
