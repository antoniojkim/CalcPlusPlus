
#include <sstream>
#include <utility>

#include "../../Functions/Functions.h"
#include "../FunctionExpression.h"

using namespace std;

namespace calcpp {

    FunctionExpression::FunctionExpression(const int functionIndex) :
        functionIndex{functionIndex} {}

    //     Expression(FUNCTION), functionIndex(functionIndex) {
    //     // Parse args
    //     if (arg != TUPLE){
    //         arg = TupleExpression::construct({arg});
    //     }
    //     if(arg->size() == signature.size()){
    //         bool onlyEmpty = true;
    //         for (auto e : *arg){
    //             if (e != EMPTY){
    //                 onlyEmpty = false;
    //                 break;
    //             }
    //         }
    //         if (onlyEmpty){ // Most cases should go here
    //             this->arg = arg;
    //             return;
    //         }
    //     }

    //     std::vector<expression> positionalArgs;
    //     positionalArgs.reserve(arg->size());

    //     int eIndex = 0;

    //     // Get Positional Args
    //     while(eIndex < arg->size() && !(arg->at(eIndex) == VAR &&
    //     arg->at(eIndex)->at(1))){
    //         positionalArgs.emplace_back(arg->at(eIndex++));
    //     }

    //     // Get Keyword Args
    //     std::map<std::string, expression> kwargs;
    //     while(eIndex < arg->size()){
    //         if (arg->at(eIndex) != VAR){
    //             throw Exception("Positional argument follows keyword argument");
    //         }
    //         auto name = arg->at(eIndex)->repr();
    //         if (kwargs.count(name) > 0){
    //             throw Exception("Keyword argument repeated: ", arg);
    //         }
    //         kwargs[name] = arg->at(eIndex++)->at(1);
    //     }

    //     std::vector<expression> args;
    //     args.reserve(signature.size());

    //     int pIndex = 0;
    //     auto s = signature.begin();
    //     auto end = signature.end();
    //     while (s != end && s->second == EMPTY && !positionalArgs.empty()){
    //         if (kwargs.count(s->first) > 0){
    //             throw Exception(repr(), " got multiple value for argument '",
    //             s->first,
    //             "'");
    //         }
    //         args.emplace_back(positionalArgs.at(0));
    //         positionalArgs.erase(positionalArgs.begin());
    //         ++s;
    //     }

    //     if (s == end){
    //         this->arg = TupleExpression::construct(std::move(args));
    //         return;
    //     }

    //     if (s->second == VARARGS){  // Move remaining positional args into varargs
    //         args.emplace_back(TupleExpression::construct(std::move(positionalArgs)));
    //         ++s;
    //     }
    //     else {
    //         for(auto p: positionalArgs){
    //             if (kwargs.count(s->first) > 0){
    //                 throw Exception(repr(), " got multiple value for argument '",
    //                 s->first, "'");
    //             }
    //             args.emplace_back(p);
    //             ++s;
    //         }
    //     }

    //     while (s != end){
    //         if (s->second == EMPTY){
    //             throw Exception(repr(), ": non-default argument follows default
    //             argument");
    //         }
    //         if (s->second == VARARGS){
    //             throw Exception(repr(), ": varargs argument follows named argument");
    //         }
    //         if (kwargs.count(s->first) > 0){
    //             args.emplace_back(kwargs.at(s->first));
    //         }
    //         else{
    //             args.emplace_back(s->second);
    //         }
    //         ++s;
    //     }

    //     this->arg = TupleExpression::construct(std::move(args));
    // }

    bool FunctionExpression::is(const Type type, const Environment& env) {
        return (type & Type::Function) != 0;
    }

    bool FunctionExpression::equals(expression e, double precision) const {
        if (e == Type::FUNCTION) { return id() == e->id(); }
        return false;
    }

    std::ostream& FunctionExpression::repr(std::ostream& out) const {
        return out << name;
    }
    std::ostream& FunctionExpression::print(std::ostream& out) const {
        return repr(out);
    }
    std::ostream& FunctionExpression::postfix(std::ostream& out) const {
        return repr(out);
    }

}  // namespace calcpp
