#pragma once

#include <string>

typedef double (*UnaryFunction)(double x);

constexpr int numFunctions = {numFunctions};
extern const std::string functionNames[numFunctions];

/*
Returns index of the function in the functionNames array.

Parameters
----------
name: The name of the function

Returns
-------
The index or -1 if the provided name is not a function.
*/
int getFunctionIndex(const std::string& name);

/*
Returns the number of arguments that a function takes in.

Parameters
----------
name: The name of the function

Returns
-------
If the name is a valid function it will return the number of arguments.
If the name is not valid, the function will return 0.
Note: a return value of -1 means that it accepts a variable number of parameters.
*/
int getFunctionNumArgs(const std::string& name);

/*
Returns the number of arguments for the function at the provided index.

Parameters
----------
index: the index of the function name

Returns
-------
If the index is valid, it will return the number of arguments.
If the index is not valid, the function will return 0.
Note: a return value of -1 means that it accepts a variable number of parameters.
*/
int getFunctionNumArgs(int index);

UnaryFunction get_unary_function(const std::string& name);
