
#include <string>

#include "../ExpressionFunctions.h"
#include "../ExpressionOperations.h"
#include "../NumericalExpression.h"

using namespace std;

namespace calcpp {

    expression NumericalExpression::derivative(const expression var) { return num(0); }
    expression NumericalExpression::integrate(const expression var) {
        return copy() * var;
    }

}  // namespace calcpp
