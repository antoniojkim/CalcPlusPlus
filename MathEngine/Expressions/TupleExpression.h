#pragma once

#include <initializer_list>
#include <list>
#include <vector>

#include <gsl/gsl_complex.h>

#include "Expression.h"

class TupleExpression: public Expression {

    std::list<expression> _data;

    TupleExpression();
    TupleExpression(std::list<expression>&& tuple);
    TupleExpression(std::initializer_list<double> tuple);
    TupleExpression(std::initializer_list<gsl_complex> tuple);

    public:
        static expression construct();
        static expression construct(std::list<expression>&& tuple);
        static expression construct(std::initializer_list<double> tuple);
        static expression construct(std::initializer_list<gsl_complex> tuple);


        expression evaluate(const Variables& vars) override;

        inline TupleExpression* tuple() override { return this; }

        inline std::list<expression>& data(){ return _data; }

        EXPRESSION_OVERRIDES

};
