#include <cmath>
#include <numeric>

#include <gsl/gsl_math.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_sf_gamma.h>

#include "../../Expressions/ExpressionFunctions.h"
#include "../../Expressions/ExpressionOperations.h"
#include "../../Expressions/VariableExpression.h"
#include "../../Scanner/scanner.h"
#include "../../Utils/Exception.h"
#include "../Functions.h"

using namespace Scanner;

namespace Function {

    // @Operator eq: = := <-
    struct eq: public OperatorFunctionExpression {
        eq(int functionIndex, expression arg): OperatorFunctionExpression(functionIndex, arg) {}

        expression eval(const Variables& vars = emptyVars) override {
            using Scanner::VAR;
            auto l = arg->at(0);
            auto r = arg->at(1)->eval(vars);
            if (l != VAR){
                throw Exception("Assignment operator expects variable. Got: ", l, ", ", r);
            }
            return VariableExpression::construct(l->repr(), r);
        }
        double value(const Variables& vars = emptyVars) const override {
            return arg->at(1)->value(vars);
        }
    };
    expression make_fe_eq(int functionIndex, expression arg){
        if (arg->size() == 2 && arg->at(0) == VAR){
            return VariableExpression::construct(arg->at(0)->repr(), arg->at(1));
        }
        return std::make_shared<Function::eq>(functionIndex, arg);
    }

}
