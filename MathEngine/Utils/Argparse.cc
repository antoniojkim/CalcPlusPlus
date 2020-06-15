
#include <map>

#include "../Expressions/Expression.h"
#include "../Expressions/TupleExpression.h"
#include "../Expressions/VariableExpression.h"
#include "Argparse.h"

using namespace Function;

Args::Args(expression args) {
    this->args.reserve(args->tuple() ? args->tuple()->size() : 1);
    auto tuple = args->tuple();
    if (tuple){
        for (auto arg : *tuple){
            insert(arg);
        }
    }
    else{
        insert(args);
    }
}

bool Args::insert(expression e){
    if (args.capacity() <= args.size()){
        return false;
    }
    // VariableExpression* var = e->variable();
    // if (var){
    //     args.emplace_back(var->getVar());
    //     kwargs[var->getName()] = var->getVar();
    //     return true;
    // }
    args.emplace_back(e);
    return true;
}

HeapArray<double> Args::array(){
    HeapArray<double> arr(args.size());
    int i = 0;
    for (auto arg : args){
        arr[i++] = arg->value();
    }
    return arr;
}
