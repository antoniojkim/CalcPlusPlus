#pragma once

#include <initializer_list>
#include <list>
#include <vector>

#include <gsl/gsl_complex.h>

#include "Expression.h"
#include "../Utils/DynamicArray.h"

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

        inline const std::list<expression>& data() const { return _data; }

        decltype(std::begin(_data)) begin() { return std::begin(_data); }
        decltype(std::end(_data)) end() { return std::end(_data); }
        size_t size() const { return _data.size(); }

        expression front(){ return _data.front(); }
        expression back(){ return _data.back(); }

        DynamicArray<double> array(const Variables& vars);
        void array(double* a, size_t size, const Variables& vars);

        EXPRESSION_OVERRIDES

};
