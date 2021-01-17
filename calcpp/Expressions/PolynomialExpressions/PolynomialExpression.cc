
// #include "../PolynomialExpression.h"



// #include <algorithm>
// #include <memory>
// #include <utility>

// #include <gsl/gsl_math.h>

// #include "../../Scanner/scanner.h"
// #include "../../Utils/Exception.h"
// #include "../ExpressionOperations.h"
// #include "../NumericalExpression.h"
// #include "../PolynomialExpression.h"

// using namespace std;
// using namespace Scanner;

// PolynomialExpression::PolynomialExpression(std::vector<expression>&& tuple): Expression(POLY), data(std::move(tuple)) {}
// PolynomialExpression::PolynomialExpression(expression tuple): Expression(POLY), data(std::move(tuple)) {}

// expression PolynomialExpression::construct(std::vector<expression>&& tuple){
//     return shared_ptr<PolynomialExpression>(new PolynomialExpression(std::move(tuple)));
// }
// expression PolynomialExpression::construct(expression tuple){
//     return shared_ptr<PolynomialExpression>(new PolynomialExpression(tuple));
// }


// expression PolynomialExpression::simplify() {
//     vector<expression> simplified;
//     simplified.reserve(data.size());
//     for (auto& expr : data){
//         simplified.emplace_back(expr->simplify());
//     }
//     return PolynomialExpression::construct(std::move(simplified));
// }
// expression PolynomialExpression::derivative(const std::string& var) {
//     vector<expression> derivatives;
//     derivatives.reserve(data.size());
//     for (auto& expr : data){
//         derivatives.emplace_back(expr->derivative(var));
//     }
//     return PolynomialExpression::construct(std::move(derivatives));
// }
// expression PolynomialExpression::integrate(const std::string& var) {
//     vector<expression> integrals;
//     integrals.reserve(data.size());
//     for (auto& expr : data){
//         integrals.emplace_back(expr->integrate(var));
//     }
//     return PolynomialExpression::construct(std::move(integrals));
// }

// expression PolynomialExpression::at(const int index) {
//     return data.at(index);
// }
// size_t PolynomialExpression::size() const { return data.size(); }

// expression PolynomialExpression::apply(TransformerFunction f){
//     std::transform(data.begin(), data.end(), data.begin(), f);
//     return copy();
// }

// bool PolynomialExpression::isComplex() const {
//     for(auto& expr : data){
//         if (expr->isComplex()){
//             return true;
//         }
//     }
//     return false;
// }
// bool PolynomialExpression::isEvaluable(const Variables& vars) const {
//     for(auto& expr : data){
//         if (!expr->isEvaluable(vars)){
//             return false;
//         }
//     }
//     return true;
// }

// expression PolynomialExpression::eval(const Variables& vars) {
//     vector<expression> evaluated;
//     evaluated.reserve(data.size());
//     for (auto& expr : data){
//         evaluated.emplace_back(expr->eval(vars));
//     }
//     return PolynomialExpression::construct(std::move(evaluated));
// }
// double PolynomialExpression::value(const Variables& vars) const { return GSL_NAN; }


// bool PolynomialExpression::equals(expression e, double precision) const {
//     if (e == TUPLE && data.size() == e->size()){
//         for (size_t i = 0; i < data.size(); ++i){
//             if(!data[i]->equals(e->at(i), precision)){
//                 return false;
//             }
//         }
//         return true;
//     }
//     return false;
// }

// std::ostream& PolynomialExpression::print(std::ostream& out, const bool pretty) const {
//     out << "(";
//     if (!data.empty()){
//         for (size_t i = 0; i < data.size(); ++i){
//             if (i != 0){
//                 out << ", ";
//             }
//             data[i]->print(out, pretty);
//         }
//     }
//     return out << ")";
// }
// std::ostream& PolynomialExpression::postfix(std::ostream& out) const {
//     out << "(";
//     if (!data.empty()){
//         for (size_t i = 0; i < data.size(); ++i){
//             if (i != 0){
//                 out << ", ";
//             }
//             data[i]->postfix(out);
//         }
//     }
//     return out << ")";
// }
