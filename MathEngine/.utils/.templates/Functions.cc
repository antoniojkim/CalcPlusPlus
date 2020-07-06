
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "Functions.h"

using namespace Function;

namespace Functions {

    #define FUNCTION_GET(Type)                              \
        const Functions::Type get##Type(const char* name){  \
            return Type##s[Functions::indexOf(name)];       \
        }                                                   \
        const Functions::Type get##Type(int index){         \
            return Type##s[index];                          \
        }

    const Functions::EvalFunction EvalFunctions[Functions::numFunctions] = {
        {EvalFunctions}
    };
    FUNCTION_GET(EvalFunction)

    const Functions::ValueFunction ValueFunctions[Functions::numFunctions] = {
        {ValueFunctions}
    };
    FUNCTION_GET(ValueFunction)

    const Functions::SimplifyFunction SimplifyFunctions[Functions::numFunctions] = {
        {SimplifyFunctions}
    };
    FUNCTION_GET(SimplifyFunction)

    const Functions::DerivativeFunction DerivativeFunctions[Functions::numFunctions] = {
        {DerivativeFunctions}
    };
    FUNCTION_GET(DerivativeFunction)

    const Functions::IntegralFunction IntegralFunctions[Functions::numFunctions] = {
        {IntegralFunctions}
    };
    FUNCTION_GET(IntegralFunction)

    const Functions::PrintFunction PrintFunctions[Functions::numFunctions] = {
        {PrintFunctions}
    };
    FUNCTION_GET(PrintFunction)

    const Functions::PostfixFunction PostfixFunctions[Functions::numFunctions] = {
        {PostfixFunctions}
    };
    FUNCTION_GET(PostfixFunction)

    {signatureDefs}

    const Function::Signature* Signatures[Functions::numFunctions] = {
        {Signatures}
    };
    const Function::Signature& getSignature(const char* name){
        return *Signatures[Functions::indexOf(name)];
    }
    const Function::Signature& getSignature(int index){
        return *Signatures[index];
    }
}
