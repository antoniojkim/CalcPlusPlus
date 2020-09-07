#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_math.h>

#include "../Scanner/scanner.h"
#include "../Utils/Types.h"

class Expression;

typedef std::shared_ptr<Expression> expression;
typedef std::map<std::string, expression> Variables;

extern const Variables emptyVars;

typedef expression(*TransformerFunction)(expression);

class Expression: public std::enable_shared_from_this<Expression> {

    public:
        const Scanner::Type kind;

        Expression(Scanner::Type kind);
        virtual ~Expression();

        virtual expression simplify();
        virtual expression derivative(const std::string& var);
        virtual expression integrate(const std::string& var);

        virtual bool isComplex() const = 0;
        virtual bool isEvaluable(const Variables& vars = emptyVars) const = 0;
        virtual bool isNumber() const { return false; }

        virtual expression eval(const Variables& vars = emptyVars) = 0;
        virtual double value(const Variables& vars = emptyVars) const = 0;
        virtual gsl_complex complex(const Variables& vars = emptyVars) const;

        virtual bool equals(expression, double precision=1e-15) const = 0;

        std::vector<double> array();
        virtual expression at(const int index);
        virtual double get(const int index);
        virtual size_t shape(const int axis) const;
        virtual size_t size() const;

        virtual expression call(expression e);
        inline expression operator()(expression e){ return call(e); }

        virtual expression apply(TransformerFunction f);
        inline expression operator()(TransformerFunction f){ return apply(f); }

        inline bool is(Scanner::Type kind) const { return this->kind == kind; }
        virtual std::string repr() const;
        virtual int id() const;

        expression copy();

        virtual std::ostream& print(std::ostream&, const bool pretty=false) const = 0;
        virtual std::ostream& postfix(std::ostream&) const = 0;

    private:
        struct gsl_expression_struct {
            Expression* e;
            const std::string var;
            Variables vars;

            gsl_expression_struct(Expression*, const std::string var = "x");
        };
        static double gsl_expression_function(double x, void* p);
        std::unique_ptr<gsl_expression_struct> gsl_params;

    public:
        virtual gsl_function function(const std::string& var = "x");

    private:
        struct ExpressionIterator {
            expression e;
            size_t index;

            ExpressionIterator(expression e, size_t index);

            expression operator*();

            bool operator==(const ExpressionIterator& other) const;
            bool operator!=(const ExpressionIterator& other) const;
            bool operator<(const ExpressionIterator& other) const;
            bool operator<=(const ExpressionIterator& other) const;
            bool operator>(const ExpressionIterator& other) const;
            bool operator>=(const ExpressionIterator& other) const;

            ExpressionIterator& operator++();
            ExpressionIterator& operator--();
        };
    public:
        ExpressionIterator begin();
        ExpressionIterator end();
};

std::ostream& operator<<(std::ostream&, const expression);

#define EXPRESSION_PARTIAL_OVERRIDES                                                \
    bool isComplex() const override;                                                \
    bool isEvaluable(const Variables& vars = emptyVars) const override;             \
    bool equals(expression, double precision) const override;                       \
    std::ostream& print(std::ostream&, const bool pretty = false) const override;   \
    std::ostream& postfix(std::ostream&) const override;

#define EXPRESSION_OVERRIDES                                                        \
    EXPRESSION_PARTIAL_OVERRIDES                                                    \
    expression eval(const Variables& vars = emptyVars) override;                    \
    double value(const Variables& vars = emptyVars) const override;
