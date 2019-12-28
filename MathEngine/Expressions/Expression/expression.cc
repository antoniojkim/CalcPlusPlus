#include "../Expression.h"

double gsl_expression_function(double x, void* params){
    return ((Expression *) params)->value(x);
}

std::ostream& operator<<(std::ostream& out, expression& e){
    return out << e.get();
}

std::ostream& operator<<(std::ostream& out, Expression* e){
    return e->print(out);
}
