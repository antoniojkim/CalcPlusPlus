#pragma once

#include <initializer_list>
#include <list>
#include <vector>

#include <gsl/gsl_complex.h>

#include "Expression.h"

class TupleExpression: public Expression {

    std::vector<expression> data;

    TupleExpression();
    TupleExpression(std::vector<expression>&& tuple);
    TupleExpression(std::list<expression>& tuple);
    TupleExpression(std::initializer_list<expression> tuple);
    TupleExpression(std::initializer_list<double> tuple);
    TupleExpression(std::initializer_list<gsl_complex> tuple);

    public:
        static expression construct();
        static expression construct(std::vector<expression>&& tuple);
        static expression construct(std::list<expression>& tuple);
        static expression construct(std::initializer_list<expression> tuple);
        static expression construct(std::initializer_list<double> tuple);
        static expression construct(std::initializer_list<gsl_complex> tuple);

        expression simplify() override;
        expression derivative(const std::string& var) override;
        expression integrate(const std::string& var) override;

        expression at(const int index) override;
        size_t size() const override;

        EXPRESSION_OVERRIDES

};
