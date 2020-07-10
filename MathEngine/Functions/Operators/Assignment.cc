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

namespace Function {

    // @Operator eq: = := <-
    namespace eq {
        expression eval(Function::Args& args) {
            using Scanner::VAR;
            auto l = args.next();
            auto r = args.next();
            if (l != VAR){
                throw Exception("Assignment operator expects variable. Got: ", l);
            }
            return VariableExpression::construct(l->repr(), r);
        }
        OPERATOR_PRINT_POSTFIX_DEFINITION('=')
    };

}
