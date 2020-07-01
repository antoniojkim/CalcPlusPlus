
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
    argnames.reserve(tokens.size());

    if (tokens.front().type != LPAREN){
        throw Exception("Invalid Signature: ", signature);
    }
    tokens.pop_front();

    while (!tokens.empty()){
        auto& var = tokens.front();
        switch(var.type){
            case COMMA:
            case RPAREN:
                tokens.pop_front();
                continue;
            case ID:
                break;
            default:
                throw Exception("Function Signature must contain only positional and named variables. Got: ", signature);
        }
        tokens.pop_front();

        auto& next = tokens.front();
        switch(next.type){
            case COMMA:
            case RPAREN:
                if (!argnames.empty() && argnames.back().second){
                    throw Exception("Positional Argument cannot follow named argument. Signature: ", signature);
                }
                argnames.emplace_back(var.lexeme, nullptr);
                tokens.pop_front();
                break;
            case EQUALS: { // Implied first named argument
                tokens.pop_front();
                list<Token> val;
                while(tokens.front().type != COMMA && tokens.front().type != RPAREN){
                    val.emplace_back(std::move(tokens.front()));
                    tokens.pop_front();
                }
                argnames.emplace_back(var.lexeme, parser.parse(val));
                break;
            }
            case ELLIPSIS:
                if (!argnames.empty() && argnames.back().second){
                    throw Exception("VarArg cannot follow named argument. Signature: ", signature);
                }
                argnames.emplace_back(var.lexeme, VarArgsExpression::construct());
                tokens.pop_front();
                break;
            default:
                throw Exception("Unexpected token ", next.lexeme, " encountered when parsing signature: ", signature);
        }
    }
}

std::unique_ptr<Args> Signature::parse(expression e) const {
    auto args = std::make_unique<Args>();
    for (auto argname : argnames){
        args->kwargs[argname.first] = argname.second;
    }
    size_t arg_i = 0;  // represents index for argname
    size_t e_i = 0;  // represents index for expression
    for (; e_i < e->size(); ++e_i){
        if (arg_i >= argnames.size()){
            throw Exception("Too many arguments given. Signature: ", *this, ". Got: ", e);
        }
        if (argnames.at(arg_i).second == VARARGS){
            // Avoid using flag variable by entering new state handling the var args case
            std::vector<expression> varargs;
            varargs.reserve(e->size() - e_i);
            for (; e_i < e->size(); ++e_i){
                if (e->at(e_i) == VAR){  // implies that it is named argument
                    break;
                }
                varargs.emplace_back(e->at(e_i));
            }
            args->kwargs[argnames.at(arg_i++).first] = TupleExpression::construct(std::move(varargs));
            break;
        }
        else if (e->at(e_i) == VAR){  // implies that it is named argument
            break;
        }
        else if (e->at(e_i) == VARARGS){  // implies that it is given argument is variadic
            throw Exception("Tuple Expansion not yet supported.");
        }
        else {
            auto argname = argnames.at(arg_i++).first;
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
