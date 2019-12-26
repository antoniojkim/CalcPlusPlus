#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include <memory>

#include "../Parser/parsetree.h"

struct Expression;

typedef std::unique_ptr<Expression> expression;

struct Expression {
  
    virtual expression simplify() = 0;
    virtual expression derivative() = 0;
    virtual expression integrate() = 0;
    
    virtual bool evaluable(){ return true; }
    virtual expression evaluate() = 0;
    virtual double value() = 0;

    virtual void setX() = 0;
    virtual void setY() = 0;

};

expression generate_expression(ParseTree*);

#endif // __EXPRESSION_H__
