#include <unordered_map>

#include "../CallableExpression.h"

using namespace std;

namespace calcpp {

    CallableExpression::CallableExpression(expression f, expression arg) :
        f{f}, arg{arg} {
        if (f == Type::FUNCTION) {
            const size_t signatureSize = f->size();
            if (arg != Type::TUPLE) {
                if (signatureSize > 1) {
                    THROW_ERROR(
                        "Function expected " << signatureSize << " arguments. Got 1");
                }
                arg = tuple(arg);
            } else {
                const size_t numArgs = arg->size();
                if (numArgs > signatureSize) {
                    THROW_ERROR(
                        "Function expected " << signatureSize << "arguments. Got "
                                             << numArgs);
                }

                std::vector<expression> pos;
                pos.reserve(numArgs);
                std::map<std::string, expression> kwargs;
                kwargs.reserve(numArgs);

                size_t i = 0;
                // Positional Args
                while (i < numArgs && arg->at(i) != Type::ASSIGNMENT) {
                    pos.emplace_back(arg->at(i++));
                }
                // kwargs Args
                while (i < numArgs) {
                    if (arg->at(i) != Type::ASSIGNMENT) {
                        THROW_ERROR("Positional arg provided after keyward argument");
                    }
                    std::ostringstream name;
                    arg->at(i)->at(0)->repr(name);
                    kwargs[name.str()] = arg->at(i)->at(1);
                    ++i;
                }

                std::vector<expression> args;
                args.reserve(signatureSize);

                i = 0;
                for (expression s : f) {
                    if (s == Type::VAR) {
                        if (i < pos.size()) {
                            args.emplace_back(pos[i++]);
                        } else {
                            std::ostringstream oss;
                            s->repr(oss);
                            const std::string name = oss.str();
                            if (kwargs.count(name) > 0) {
                                args.emplace_back(kwargs[name]);
                                kwargs.erase(name);
                            } else {
                                THROW_ERROR("Not enough positional arguments provided");
                            }
                        }
                    } else if (s == Type::VARARG) {
                        std::vector<expression> vararg(pos.begin() + i, pos.end());
                        args.emplace_back(tuple(std::move(varargs)));
                        i = pos.size();
                    } else if (s == Type::ASSIGNMENT) {
                        std::ostringstream oss;
                        s->at(0)->repr(oss);
                        const std::string name = oss.str();
                        if (kwargs.count(name) > 0) {
                            if (i < pos.size()) {
                                THROW_ERROR("Multiple values provided for " << name);
                            }
                            args.emplace_back(kwargs[name]);
                            kwargs.erase(name);
                        } else if (i < pos.size()) {
                            args.emplace_back(pos[i++]);
                        } else {
                            args.emplace_back(s->at(1));
                        }
                    }
                }
                if (i < pos.size()) {
                    THROW_ERROR(
                        "Too many positional arguments supplied. "
                        << (pos.size() - i) << " unused positional arguments");
                } else if (kwargs.size() > 0) {
                    THROW_ERROR(
                        "Function got an unexpected keyword argument: "
                        << kwargs.begin()->first);
                }
                arg = tuple(std::move(args));
            }
        }
    }

    expression CallableExpression::construct(expression f, expression arg) {
        return shared_ptr<CallableExpression>(new CallableExpression(f, arg));
    }

    expression CallableExpression::at(const int index) {
        switch (index) {
            case 0:
                return f;
            case 1:
                return arg;
            default:
                THROW_ERROR("CallableExpression::at Invalid index: " << index);
        }
    }

    expression CallableExpression::eval(const Environment& env) {
        return f->call(arg->eval(env));
    }
    long double CallableExpression::value(const Environment& env) const {
        return eval(env)->value();
    }

    bool CallableExpression::equals(expression e, double precision) const {
        return e->is(Type::CALLABLE) && f->equals(e->at(0), precision) &&
               arg->equals(e->at(1), precision);
    }
    bool CallableExpression::is(Type type, const Environment& env) const {
        switch (type) {
            case Type::EVALUABLE:
                return arg->is(type, env);
            case Type::CALLABLE:
                return true;
            default:
                return false;
        }
    }

    std::ostream& CallableExpression::repr(std::ostream& out) const {
        return out << "call(" << f->repr() << ", " << arg->repr() << ")";
    }
    std::ostream& CallableExpression::str(std::ostream& out) const {
        if (arg->is(Type::TUPLE)) {
            return out << f->repr() << arg->str();
        } else {
            return out << f->repr() << "(" << arg->str() << ")";
        }
    }
    std::ostream& CallableExpression::postfix(std::ostream& out) const {
        return out << arg->postfix() << " " << f->repr();
    }

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
}  // namespace calcpp
