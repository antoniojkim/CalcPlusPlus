#include "../Expression.h"

Expression::ExpressionIterator::ExpressionIterator(expression e, size_t index):
    e{e}, index{index} {}

expression Expression::ExpressionIterator::operator*(){
    return e->at(index);
}

bool Expression::ExpressionIterator::operator==(const ExpressionIterator& other) const {
    return e == other.e && index == other.index;
}
bool Expression::ExpressionIterator::operator!=(const ExpressionIterator& other) const {
    return e != other.e || index != other.index;
}
bool Expression::ExpressionIterator::operator<(const ExpressionIterator& other) const {
    return e == other.e && index < other.index;
}
bool Expression::ExpressionIterator::operator<=(const ExpressionIterator& other) const {
    return e == other.e && index <= other.index;
}
bool Expression::ExpressionIterator::operator>(const ExpressionIterator& other) const {
    return e == other.e && index > other.index;
}
bool Expression::ExpressionIterator::operator>=(const ExpressionIterator& other) const {
    return e == other.e && index >= other.index;
}

Expression::ExpressionIterator& Expression::ExpressionIterator::operator++(){
    ++index;
    return *this;
}
Expression::ExpressionIterator& Expression::ExpressionIterator::operator--(){
    --index;
    return *this;
}

Expression::ExpressionIterator Expression::begin(){
    return Expression::ExpressionIterator(copy(), 0);
}
Expression::ExpressionIterator Expression::end(){
    return Expression::ExpressionIterator(copy(), size());
}
