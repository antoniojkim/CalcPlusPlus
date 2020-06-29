
#include <iomanip>
#include <memory>

#include <gsl/gsl_math.h>

#include "../../Scanner/scanner.h"
#include "../../Utils/exceptions.h"
#include "../NumericalExpression.h"
#include "../UnitConversionExpression/Units.h"
#include "../UnitExpression.h"
#include "../TupleExpression.h"
#include "../VariableExpression.h"
#include "Constants.h"

using namespace std;
using namespace Scanner;

VarArgsExpression::VarArgsExpression(expression e): Expression{VARARGS}, e{e} {}

expression VarArgsExpression::construct(expression e){
    return shared_ptr<VarArgsExpression>(new VarArgsExpression(e));
}

expression VarArgsExpression::at(const int index) {

}
std::string VarArgsExpression::repr() const {

}

EXPRESSION_OVERRIDES
