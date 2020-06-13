#pragma once

#include <initializer_list>
#include <list>
#include <vector>

#include <gsl/gsl_complex.h>

#include "Expression.h"
#include "../Utils/HeapArray.h"

class TupleExpression: public Expression {

    std::list<expression> data;

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

        decltype(std::begin(data)) begin() { return std::begin(data); }
        decltype(std::end(data)) end() { return std::end(data); }
        size_t size() const { return data.size(); }

        expression front(){ return data.front(); }
        expression back(){ return data.back(); }

        HeapArray<double> array(const Variables& vars);
        void array(double* a, size_t size, const Variables& vars);

        EXPRESSION_OVERRIDES

};
