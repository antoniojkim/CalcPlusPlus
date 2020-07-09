
/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include "Functions.h"

using namespace Function;

namespace Functions {

    #define FUNCTION_GET(Type)                              \
        const Functions::Type get##Type(const char* name){  \
            return Type##s[Functions::indexOf(name)];       \
        }                                                   \
        const Functions::Type get##Type(int index){         \
            return Type##s[index];                          \
        }

    const Functions::EvalFunction EvalFunctions[Functions::numFunctions] = {
        mod::eval, bitwise_and::eval, mul::eval, pow::eval, add::eval, sub::eval, div::eval,
		floordiv::eval, eq::eval, eq::eval, lshift::eval, eq::eval, rshift::eval, Beta::eval,
		Betainc::eval, choose::eval, Cholesky::eval, LU::eval, LUsolve::eval, permute::eval,
		pow::eval, bitwise_xor::eval, nullptr, absdev::eval, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, add::eval, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, argmax::eval, argmin::eval, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		lag1::eval, bin::eval, bitwise_and::eval, bitwise_or::eval, bitwise_xor::eval, nullptr,
		nullptr, choose::eval, choose::eval, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, cubic::eval, cubicc::eval, nullptr, deriv::eval, det::eval, nullptr,
		diff::eval, div::eval, eq::eval, nullptr, nullptr, nullptr, nullptr, fcmp::eval,
		fft::eval, floordiv::eval, frexp::eval, nullptr, gamma_inc::eval, gamma_inc_P::eval,
		gamma_inc_Q::eval, gamma_inc::eval, gamma_inc_P::eval, gamma_inc_Q::eval, nullptr,
		nullptr, gcd::eval, hex::eval, hypot::eval, ifft::eval, integral::eval, kurtosis::eval,
		kurtosis::eval, lag1::eval, lcm::eval, ldexp::eval, nullptr, nullptr, nullptr,
		lnBeta::eval, lnchoose::eval, lnchoose::eval, lndet::eval, nullptr, nullptr, nullptr,
		lnpermute::eval, lnpermute::eval, lnpoch::eval, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, logn::eval, lshift::eval, max::eval, argmax::eval, mean::eval,
		median::eval, min::eval, argmin::eval, mod::eval, mul::eval, neg::eval, num::eval,
		permute::eval, permute::eval, poch::eval, pochrel::eval, pow::eval, quad::eval,
		quadc::eval, nullptr, rshift::eval, sd::eval, nullptr, nullptr, nullptr, nullptr,
		skew::eval, LUsolve::eval, nullptr, nullptr, sd::eval, sd::eval, sub::eval, nullptr,
		nullptr, taylorcoeff::eval, tss::eval, var::eval, var::eval, bitwise_or::eval
    };
    FUNCTION_GET(EvalFunction)

    const Functions::ValueFunction ValueFunctions[Functions::numFunctions] = {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, abs::value, nullptr, acos::value, acosh::value,
		acot::value, acoth::value, acsc::value, acsch::value, nullptr, acos::value,
		acosh::value, acot::value, acoth::value, acsc::value, acsch::value, acos::value,
		acosh::value, acot::value, acoth::value, acsc::value, acsch::value, asec::value,
		asech::value, asin::value, asinh::value, atan::value, atanh::value, nullptr, nullptr,
		asec::value, asech::value, asin::value, asinh::value, atan::value, atanh::value,
		asec::value, asech::value, asin::value, asinh::value, atan::value, atanh::value,
		nullptr, nullptr, nullptr, nullptr, nullptr, cb::value, cbrt::value, nullptr, nullptr,
		cos::value, cosh::value, cot::value, coth::value, csc::value, csch::value, nullptr,
		nullptr, deg::value, nullptr, nullptr, dfact::value, nullptr, nullptr, nullptr,
		exp::value, exp2::value, expm1::value, fact::value, nullptr, nullptr, nullptr, nullptr,
		gamma::value, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, gammainv::value,
		gammastar::value, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, ln::value, ln1p::value, ln2::value, nullptr, nullptr,
		nullptr, nullptr, lndfact::value, lnfact::value, lngamma::value, nullptr, nullptr,
		nullptr, log::value, log::value, ln1p::value, log1pm::value, ln2::value, logabs::value,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, neg::value, num::value, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, rad::value, nullptr, nullptr, sec::value, sech::value, sin::value, sinh::value,
		nullptr, nullptr, sqr::value, sqrt::value, nullptr, nullptr, nullptr, tan::value,
		tanh::value, nullptr, nullptr, nullptr, nullptr, nullptr
    };
    FUNCTION_GET(ValueFunction)

    const Functions::SimplifyFunction SimplifyFunctions[Functions::numFunctions] = {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr
    };
    FUNCTION_GET(SimplifyFunction)

    const Functions::DerivativeFunction DerivativeFunctions[Functions::numFunctions] = {
        nullptr, nullptr, mul::derivative, pow::derivative, add::derivative, sub::derivative,
		div::derivative, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, pow::derivative, nullptr, abs::derivative,
		nullptr, acos::derivative, acosh::derivative, acot::derivative, acoth::derivative,
		acsc::derivative, acsch::derivative, add::derivative, acos::derivative,
		acosh::derivative, acot::derivative, acoth::derivative, acsc::derivative,
		acsch::derivative, acos::derivative, acosh::derivative, acot::derivative,
		acoth::derivative, acsc::derivative, acsch::derivative, asec::derivative,
		asech::derivative, asin::derivative, asinh::derivative, atan::derivative,
		atanh::derivative, nullptr, nullptr, asec::derivative, asech::derivative,
		asin::derivative, asinh::derivative, atan::derivative, atanh::derivative,
		asec::derivative, asech::derivative, asin::derivative, asinh::derivative,
		atan::derivative, atanh::derivative, nullptr, nullptr, nullptr, nullptr, nullptr,
		cb::derivative, cbrt::derivative, nullptr, nullptr, cos::derivative, cosh::derivative,
		cot::derivative, coth::derivative, csc::derivative, csch::derivative, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, div::derivative, nullptr, exp::derivative,
		exp2::derivative, expm1::derivative, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, ln::derivative, ln1p::derivative, ln2::derivative, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, log::derivative,
		log::derivative, ln1p::derivative, nullptr, ln2::derivative, nullptr, logn::derivative,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, mul::derivative,
		neg::derivative, nullptr, nullptr, nullptr, nullptr, nullptr, pow::derivative, nullptr,
		nullptr, nullptr, nullptr, nullptr, sec::derivative, sech::derivative, sin::derivative,
		sinh::derivative, nullptr, nullptr, sqr::derivative, sqrt::derivative, nullptr, nullptr,
		sub::derivative, tan::derivative, tanh::derivative, nullptr, nullptr, nullptr, nullptr,
		nullptr
    };
    FUNCTION_GET(DerivativeFunction)

    const Functions::IntegralFunction IntegralFunctions[Functions::numFunctions] = {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr
    };
    FUNCTION_GET(IntegralFunction)

    const Functions::PrintFunction PrintFunctions[Functions::numFunctions] = {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, choose::print, nullptr, nullptr,
		nullptr, permute::print, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, cb::print, nullptr, choose::print,
		choose::print, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, permute::print, permute::print, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, sqr::print, sqrt::print, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr
    };
    FUNCTION_GET(PrintFunction)

    const Functions::PostfixFunction PostfixFunctions[Functions::numFunctions] = {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
		nullptr, nullptr
    };
    FUNCTION_GET(PostfixFunction)

    const Function::Signature sig_1_f_539(1, false, {});
	const Function::Signature sig_2_f_539(2, false, {});
	const Function::Signature sig_3_f_539(3, false, {});
	const Function::Signature sig_4_f_539(4, false, {});
	const Function::Signature sig_0_t_539(0, true, {});
	const Function::Signature sig_0_t_359(0, true, {1});
	const Function::Signature sig_2_f_119(2, false, {GSL_NAN});
	const Function::Signature sig_1_f_119(1, false, {GSL_NAN});
	const Function::Signature sig_3_f_119(3, false, {GSL_NAN});
	const Function::Signature sig_2_f_169(2, false, {1e-8});

    const Function::Signature* Signatures[Functions::numFunctions] = {
        &sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539,
		&sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539,
		&sig_2_f_539, &sig_2_f_539, &sig_3_f_539, &sig_2_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_1_f_539, &sig_0_t_539,
		&sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_2_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_1_f_539, &sig_0_t_539, &sig_0_t_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_0_t_539, &sig_1_f_539, &sig_2_f_539,
		&sig_2_f_539, &sig_2_f_539, &sig_1_f_539, &sig_1_f_539, &sig_2_f_539, &sig_2_f_539,
		&sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_4_f_539, &sig_4_f_539, &sig_1_f_539, &sig_2_f_119, &sig_1_f_539, &sig_1_f_539,
		&sig_1_f_119, &sig_2_f_539, &sig_2_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_1_f_539, &sig_2_f_169, &sig_1_f_539, &sig_2_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539,
		&sig_1_f_539, &sig_1_f_539, &sig_0_t_539, &sig_1_f_539, &sig_0_t_539, &sig_1_f_539,
		&sig_3_f_119, &sig_0_t_539, &sig_0_t_539, &sig_0_t_539, &sig_0_t_539, &sig_2_f_539,
		&sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539,
		&sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_2_f_539, &sig_2_f_539,
		&sig_2_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_1_f_539, &sig_2_f_539, &sig_2_f_539, &sig_0_t_539, &sig_0_t_539, &sig_0_t_539,
		&sig_0_t_539, &sig_0_t_539, &sig_0_t_539, &sig_2_f_539, &sig_2_f_539, &sig_1_f_539,
		&sig_1_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539, &sig_2_f_539,
		&sig_3_f_539, &sig_3_f_539, &sig_1_f_539, &sig_2_f_539, &sig_0_t_359, &sig_1_f_539,
		&sig_1_f_539, &sig_1_f_539, &sig_1_f_539, &sig_0_t_539, &sig_2_f_539, &sig_1_f_539,
		&sig_1_f_539, &sig_0_t_359, &sig_0_t_359, &sig_2_f_539, &sig_1_f_539, &sig_1_f_539,
		&sig_2_f_539, &sig_0_t_539, &sig_0_t_359, &sig_0_t_359, &sig_2_f_539
    };
    const Function::Signature& getSignature(const char* name){
        return *Signatures[Functions::indexOf(name)];
    }
    const Function::Signature& getSignature(int index){
        return *Signatures[index];
    }
}
