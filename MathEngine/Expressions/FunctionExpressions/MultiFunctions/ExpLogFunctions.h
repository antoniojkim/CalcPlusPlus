#pragma once

#include <list>
#include <cmath>

#include "../../Expression.h"
#include "../FunctionDirectory.h"

using namespace std;

double f_logn(list<expression>& args, const Variables& vars){
    auto arg = args.begin();
    double a = (*(arg++))->value(vars);
    double b = (*arg)->value(vars);
    return log(a) / log(b);
}
