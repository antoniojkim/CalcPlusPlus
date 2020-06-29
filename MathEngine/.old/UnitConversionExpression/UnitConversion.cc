
#include <cmath>
#include <iomanip>
#include <sstream>

#include "../../Utils/exceptions.h"
#include "../InvalidExpression.h"
#include "../UnitExpression.h"
#include "Units.h"

using namespace std;

expression convert(const BaseUnitExpression& from, const BaseUnitExpression& to){
    if (from.type != to.type){
        return InvalidExpression::construct(Exception("Invalid Unit Conversion: ", from.abbr, " -> ", to.abbr));
    }
    return ConvertedUnitExpression::construct(from.type, to.abbr, from.val / to.val);
}

UnitType operator*(UnitType t1, UnitType t2){
	if (t1 == DISTANCE && t2 == DISTANCE){
		return AREA;
	}
	if ((t1 == DISTANCE && t2 == AREA) || (t1 == AREA && t2 == VOLUME)){
		return VOLUME;
	}
	if (t1 == TIME && t2 == TIME){
		return TIMESQUARED;
	}
	if ((t1 == MASS && t2 == ACCELERATION) || (t1 == ACCELERATION && t2 == MASS) ||
		(t1 == MASSPERTIMESQUARED && t2 == DISTANCE) ||
		(t1 == DISTANCE && t2 == MASSPERTIMESQUARED)){
		return FORCE;
	}
	if ((t1 == MASS && t2 == AREA) || (t1 == AREA && t2 == MASS)){
		return MASSAREA;
	}
	if ((t1 == FORCE && t2 == DISTANCE) || (t1 == DISTANCE && t2 == FORCE)){
		return ENERGY;
	}

	return NONE;
}

expression operator*(const BaseUnitExpression& unit1, const BaseUnitExpression& unit2){
    auto newType = unit1.type * unit2.type;
    if (newType == NONE) {
        return InvalidExpression::construct(Exception("Invalid Unit: ", unit1.abbr, " * ", unit2.abbr));
    }
    ostringstream newabbr;
    newabbr << unit1.abbr << "*" << unit2.abbr;
    return BaseUnitExpression::construct(newType, newabbr.str(), unit1.val * unit2.val);
}
expression operator*(const BaseUnitExpression& unit1, const expression expr){
    return BaseUnitExpression::construct(unit1.type, unit1.abbr, unit1.val * expr->value());
}

UnitType operator/(UnitType t1, UnitType t2){
	if (t1 == DISTANCE){
		switch (t2){
			case TIME:
				return SPEED;
			case TIMESQUARED:
				return ACCELERATION;
			default:
				return NONE;
		}
	}
	else if (t1 == MASSDISTANCE && t2 == TIMESQUARED){
		return FORCE;
	}
	else if (t1 == MASSAREA && t2 == TIMESQUARED){
		return ENERGY;
	}
	return NONE;
}

expression operator/(const BaseUnitExpression& unit1, const BaseUnitExpression& unit2){
    auto newType = unit1.type / unit2.type;
    if (newType == NONE) {
        return InvalidExpression::construct(Exception("Invalid Unit: ", unit1.abbr, " / ", unit2.abbr));
    }
    ostringstream newabbr;
    newabbr << unit1.abbr << "/" << unit2.abbr;
    return BaseUnitExpression::construct(newType, newabbr.str(), unit1.val / unit2.val);
}
expression operator/(const BaseUnitExpression& unit1, const expression expr){
    return BaseUnitExpression::construct(unit1.type, unit1.abbr, unit1.val / expr->value());
}

UnitType operator^(UnitType t1, int n){
	if (t1 == DISTANCE){
		switch(n){
			case 2:
				return AREA;
			case 3:
				return VOLUME;
			default:
				return NONE;
		}
	}
	else if (t1 == TIME && n == 2){
		return TIMESQUARED;
	}
	return NONE;
}

expression operator^(const BaseUnitExpression& unit1, const expression expr){
    double n = expr->value();
    if (std::trunc(n) != n){
        return InvalidExpression::construct(Exception("Invalid Unit: ", unit1.abbr, " ^ ", n));
    }
    auto newType = unit1.type ^ (int) n;
    if (newType == NONE) {
        return InvalidExpression::construct(Exception("Invalid Unit: ", unit1.abbr, " ^ ", n));
    }
    ostringstream newabbr;
    newabbr << unit1.abbr << "^" << int(n);
    return BaseUnitExpression::construct(newType, newabbr.str(), std::pow(unit1.val, n));
}
