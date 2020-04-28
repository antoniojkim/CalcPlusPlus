#pragma once

#include <list>
#include <cmath>

#include "../../Expression.h"
#include "../FunctionDirectory.h"

double f_logn(const std::list<expression>& args, const Variables& vars){
    auto arg = args.begin();
    double a = (*(arg++))->value(vars);
    double b = (*arg)->value(vars);
    return log(a) / log(b);
}
