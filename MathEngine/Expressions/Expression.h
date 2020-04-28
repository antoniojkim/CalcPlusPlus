#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_math.h>

struct Expression;

struct BaseUnitExpression;
struct BinExpression;
struct HexExpression;
struct InvalidExpression;
struct MatrixExpression;
struct TupleExpression;
struct VariableExpression;

typedef std::shared_ptr<Expression> expression;
typedef std::unordered_map<std::string, expression> Variables;

double gsl_expression_function(double x, void* params);

struct Expression: public std::enable_shared_from_this<Expression> {

    virtual expression simplify() = 0;
    virtual expression derivative(const std::string& var) = 0;
    virtual expression integrate(const std::string& var) = 0;

    virtual bool evaluable() const = 0;
    virtual expression evaluate();
    virtual expression evaluate(const Variables& vars);

    virtual gsl_function function();

    virtual double value() const;
    virtual double value(const Variables& vars) const = 0;

    virtual gsl_complex complex() const;
    virtual gsl_complex complex(const Variables& vars) const;

    virtual const inline BaseUnitExpression* unit() const { return nullptr; }
    virtual const inline BinExpression* bin() const { return nullptr; }
    virtual const inline HexExpression* hex() const { return nullptr; }
    virtual const inline InvalidExpression* invalid() const { return nullptr; }
    virtual const inline MatrixExpression* matrix() const { return nullptr; }
    virtual const inline TupleExpression* tuple() const { return nullptr; }
    virtual const inline VariableExpression* variable() const { return nullptr; }

    virtual bool isComplex() const = 0;

    expression copy();

    virtual std::ostream& print(std::ostream&) const = 0;
    virtual std::ostream& postfix(std::ostream&) const = 0;
    virtual bool prettyprint(std::ostream&) const;

};

std::ostream& operator<<(std::ostream&, const expression);

#define EXPRESSION_OVERRIDES                                       \
    expression simplify() override;                                \
    expression derivative(const std::string& var = "x") override;  \
    expression integrate(const std::string& var = "x") override;   \
    bool evaluable() const override;                               \
    double value(const Variables& vars) const override;            \
    bool isComplex() const override;                               \
    std::ostream& print(std::ostream&) const override;             \
    std::ostream& postfix(std::ostream&) const override;
