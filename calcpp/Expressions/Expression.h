#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <gsl/gsl_complex.h>
#include <gsl/gsl_math.h>

#include "../Utils/Types.h"
#include "Environment.h"
#include "Types.h"

namespace calcpp {

    class Expression;
    typedef std::shared_ptr<Expression> expression;

    typedef expression (*TransformerFunction)(expression);

    class Expression: public std::enable_shared_from_this<Expression> {
      public:
        virtual expression simplify();
        virtual expression derivative(const expression var);
        virtual expression integrate(const expression var);

        virtual expression eval(const Environment& env = defaultEnv);
        virtual Double value(const Environment& env = defaultEnv) const = 0;
        virtual gsl_complex complex(const Environment& env = defaultEnv) const;

        virtual bool is(const Type type, const Environment& env = defaultEnv) const = 0;
        virtual bool equals(expression, const double precision = 1e-15) const = 0;

        std::vector<Double> array();
        virtual expression at(const int index);
        virtual Double get(const int index);
        virtual size_t shape(const int axis) const;
        virtual size_t size() const;

        virtual expression call(expression e) const;
        inline expression operator()(expression e) { return call(e); }

        virtual expression apply(TransformerFunction f);
        inline expression operator()(TransformerFunction f) { return apply(f); }

        virtual unsigned int id() const;

        expression copy();

#define OSTREAM_WRAPPER(name)                                                          \
  private:                                                                             \
    struct expression_##name {                                                         \
        expression e;                                                                  \
        friend std::ostream& operator<<(std::ostream&, const expression_##name&);      \
    };                                                                                 \
                                                                                       \
  public:                                                                              \
    expression_##name name() const;                                                    \
    virtual std::ostream& name(std::ostream&) const = 0;

        // To get an explicit print out of the expression object
        OSTREAM_WRAPPER(repr);
        // To get the pretty output for display
        OSTREAM_WRAPPER(str);
        // To get the postfix form of the epxression object
        OSTREAM_WRAPPER(postfix);

      private:
        struct gsl_expression_struct {
            Expression* e;
            const std::string var;
            Environment env;

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

}  // namespace calcpp

std::ostream& operator<<(std::ostream&, const calcpp::expression);

#define EXPRESSION_PARTIAL_OVERRIDES                                                   \
    bool equals(expression, double precision) const override;                          \
    bool is(Type type, const Environment& env = defaultEnv) const override;            \
    std::ostream& repr(std::ostream&) const override;                                  \
    std::ostream& str(std::ostream&) const override;                                   \
    std::ostream& postfix(std::ostream&) const override;

#define EXPRESSION_OVERRIDES                                                           \
    EXPRESSION_PARTIAL_OVERRIDES                                                       \
    expression eval(const Environment& env = defaultEnv) override;                     \
    Double value(const Environment& env = defaultEnv) const override;

#define DECLARE_TEMPLATE_CONSTRUCTOR(name)                                             \
    template<typename... Args>                                                         \
    friend expression name(Args&&... args);

#define DECLARE_INITIALIZER_LIST_CONSTRUCTOR(name)                                     \
    template<typename T>                                                               \
    friend expression name(std::initializer_list<T> args);

#define DEFINE_TEMPLATE_CONSTRUCTOR(ExprName, name)                                    \
    template<typename... Args>                                                         \
    inline expression name(Args&&... args) {                                           \
        return std::shared_ptr<ExprName##Expression>(                                  \
            new ExprName##Expression(std::forward<Args>(args)...));                    \
    }

#define DEFINE_INITIALIZER_LIST_CONSTRUCTOR(ExprName, name)                            \
    template<typename T>                                                               \
    inline expression name(std::initializer_list<T> args) {                            \
        return std::shared_ptr<ExprName##Expression>(                                  \
            new ExprName##Expression(std::forward<std::initializer_list<T>>(args)));   \
    }
