
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "Functions.h"

using namespace Function;

namespace Functions {

	FunctionConstructor functionConstructors[Functions::numFunctions] = {
		{FunctionConstructors}
	};

	expression construct(const int functionIndex, const expression arg){
		return functionConstructors[functionIndex](functionIndex, arg);
	}

	bool functionIsOperator[Functions::numFunctions] = {
		{FunctionIsOperator}
	};

	bool isOperator(const char* name){
		return functionIsOperator[Functions::indexOf(name)];
	}
	bool isOperator(const int functionIndex){
		return functionIsOperator[functionIndex];
	}
}
