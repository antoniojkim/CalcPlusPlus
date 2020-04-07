#pragma once

#include <list>
#include <cmath>

#include "../../Expression.h"
#include "../MultiFunctionDirectory.h"

using namespace std;

double f_logn(list<expression>& args){
    auto arg = args.begin();
    double a = (*(arg++))->value();
    double b = (*arg)->value();
    return log(a) / log(b);
}
