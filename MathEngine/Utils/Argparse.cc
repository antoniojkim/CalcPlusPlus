
#include <list>
#include <map>

#include "../Expressions/Expression.h"
#include "../Expressions/ExpressionOperations.h"
#include "../Expressions/TupleExpression.h"
#include "../Expressions/VariableExpression.h"
#include "../Parser/modifiedShuntingYard.h"
#include "../Scanner/scanner.h"
#include "../Utils/Exception.h"
#include "Argparse.h"

using namespace std;
using namespace Function;
using namespace Scanner;

namespace Function {
    std::ostream& operator<<(std::ostream& out, Args& args){
        out << "(";
        bool first = true;
        for (auto arg : args){
            if (first){ first = false; }
            else      { out << ", ";   }
            out << arg.first << "=" << arg.second;
        }
        return out << ")";
    }
    std::ostream& operator<<(std::ostream& out, Signature& signature){
        out << "(";
        bool first = true;
        for (auto arg : signature.argnames){
            if (first){ first = false; }
            else      { out << ", ";   }
            out << arg;
        }
        return out << ")";
    }
}

const ModifiedShuntingYard parser;

Signature::Signature(const std::string& signature): signature{signature} {
    // Parse the signature. It should be a valid expression containing only variables.
    list<Token> tokens;
    scan(signature, tokens);
    auto signatureExpr = parser.parse(tokens);
    if (signatureExpr != TUPLE){
        throw Exception("Function Signature must be a tuple. Got: ", signature);
    }
    this->argnames.reserve(signatureExpr->size());
    // Loop through the parsed signature verifying its validity.
    size_t i = 0;
    for(; i < signatureExpr->size(); ++i){
        auto var = signatureExpr->at(i)->eval();
        if (var == VAR){
            this->argnames.emplace_back(var);
            if (var->at(0)){  // implies first named argument
                ++i;
                break;
            }
        }
        else if (var == VARARGS){  // implies varargs
            this->argnames.emplace_back(var);
            ++i;
            break;
        }
        else{
            throw Exception("Function Signature must contain only variables and default arguments. Got: ", signatureExpr);
        }
    }
    for(; i < signatureExpr->size(); ++i){
        auto var = signatureExpr->at(i)->eval();
        if (var == VAR){
            if (!var->at(0)){
                throw Exception("Positional argument cannot follow named argument in function signature. Got: ", signature);
            }
            this->argnames.emplace_back(var);
        }
        else if (var == VARARGS){
            throw Exception("varargs cannot follow named argument in function signature. Got: ", signature);
        }
        else{
            throw Exception("Function Signature must contain only variables and default arguments. Got: ", signatureExpr);
        }
    }
}

std::unique_ptr<Args> Signature::parse(expression e) const {
    auto args = std::make_unique<Args>();
    for (auto argname : argnames){
        args->kwargs[argname->repr()] = argname->at(0);
    }
    size_t arg_i = 0;  // represents index for argname
    size_t e_i = 0;  // represents index for expression
    for (; e_i < e->size(); ++e_i){
        if (arg_i >= argnames.size()){
            throw Exception("Too many arguments given. Signature: ", *this, ". Got: ", e);
        }
        if (argnames.at(arg_i) == VARARGS){
            // Avoid using flag variable by entering new state handling the var args case
            std::vector<expression> varargs;
            varargs.reserve(e->size() - e_i);
            for (; e_i < e->size(); ++e_i){
                if (e->at(e_i) == VAR){  // implies that it is named argument
                    break;
                }
                varargs.emplace_back(e->at(e_i));
            }
            args->kwargs[argnames.at(arg_i++)->at(0)->repr()] = TupleExpression::construct(std::move(varargs));
            break;
        }
        else if (e->at(e_i) == VAR){  // implies that it is named argument
            break;
        }
        else if (e->at(e_i) == VARARGS){  // implies that it is given argument is variadic
            throw Exception("Tuple Expansion not yet supported.");
        }
        else {
            auto argname = argnames.at(arg_i++)->repr();
            if (!args->kwargs[argname]){
                args->kwargs[argname] = e->at(e_i);
            }
            else{
                throw Exception("Function got multiple value for argument '", argname, "'. Signature: ", signature);
            }
        }
    }
    for (; e_i < e->size(); ++e_i){
        if (e->at(e_i) == VAR){  // implies that it is named argument
            auto key = e->at(e_i)->repr();
            if (args->kwargs.count(key) == 0){
                throw Exception("Function got an unexpected keyword argument '", key, "'. Signature: ", signature);
            }
            else if (args->kwargs[key]){
                throw Exception("Function got multiple value for argument '", key, "'. Signature: ", signature);
            }
            args->kwargs[key] = e->at(e_i)->at(0);
        }
        else {
            throw Exception("Positional argument follows keyword argument. Signature: ", signature);
        }
    }
    return args;
}
