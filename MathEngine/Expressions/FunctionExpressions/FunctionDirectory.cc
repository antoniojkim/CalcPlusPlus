#include "FunctionDirectory.h"
#include "../../Utils/exceptions.h"

#include <cmath>
#include <gsl/gsl_math.h>
#include <unordered_map>

using namespace std;

unordered_map<string, UnaryFunction> unary_function_map {
    {"sin", sin},
    {"cos", cos},
    {"tan", tan},
};

UnaryFunction get_unary_function(const string& name){
    if (unary_function_map.count(name) > 0){
        return unary_function_map[name];
    }
    throw Exception("Unknown Unary Function: ", name);
}