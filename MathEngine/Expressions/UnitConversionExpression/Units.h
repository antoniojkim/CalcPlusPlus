#pragma once

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

#include <gsl/gsl_const_mksa.h>
#include <gsl/gsl_const_num.h>

#include "../../Utils/BinarySearch.h"

enum UnitType {
	NONE,
	DISTANCE,
	TIME,
	TIMESQUARED,
	SPEED,
	ACCELERATION,
	AREA,
	VOLUME,
	MASS,
	FORCE,
	MASSDISTANCE,
	MASSPERTIMESQUARED,
	ENERGY,
	MASSAREA
};

constexpr const int numUnits = 161;
constexpr const char* unitNames[numUnits] = {
	"acre", "astronomical_unit", "attogram", "attometer", "attometerscubed",
	"attometerssquared", "attosecond", "barn", "btu", "calorie", "canadian_gallon", "carat",
	"centimeter", "century", "cup", "decade", "decameter", "decimeter", "dyne",
	"electron_volt", "erg", "exagram", "exameter", "exameterscubed", "exameterssquared",
	"exasecond", "fathom", "femtogram", "femtometer", "femtometerscubed",
	"femtometerssquared", "femtosecond", "fluid_ounce", "foot", "gigagram", "gigameter",
	"gigameterscubed", "gigameterssquared", "gigasecond", "gram", "gram_force", "grammeter",
	"grammeterspersecondsquared", "grammeterssquared", "grammeterssquaredpersecondsquared",
	"grampersecondsquared", "grav_accel", "hectare", "hectometer", "hour", "inch", "joule",
	"kilogram", "kilometer", "kilometers_per_hour", "kilometerscubed", "kilometerssquared",
	"kilopound_force", "kilosecond", "knot", "light_year", "liter", "mass_electron",
	"mass_muon", "mass_neutron", "mass_proton", "megagram", "megameter", "megameterscubed",
	"megameterssquared", "megasecond", "meter", "meterscubed", "meterspersecond",
	"meterspersecondsquared", "meterssquared", "metric_ton", "microgram", "microliter",
	"micrometer", "micrometerscubed", "micrometerssquared", "microsecond", "mil", "mile",
	"miles_per_hour", "millenium", "milligram", "milliliter", "millimeter",
	"millimeterscubed", "millimeterssquared", "millisecond", "minute", "month", "nanogram",
	"nanometer", "nanometerscubed", "nanometerssquared", "nanosecond", "nautical_mile",
	"newton", "newton_meter", "ounce_mass", "petagram", "petameter", "petameterscubed",
	"petameterssquared", "petasecond", "picogram", "picometer", "picometerscubed",
	"picometerssquared", "picosecond", "pint", "pound_force", "pound_mass", "poundal",
	"quart", "rydberg", "second", "secondsquared", "solar_mass", "speed_of_light",
	"tablespoon", "teaspoon", "teragram", "terameter", "terameterscubed",
	"terameterssquared", "terasecond", "therm", "ton", "troy_ounce", "uk_gallon", "uk_ton",
	"unified_atomic_mass", "us_gallon", "week", "yard", "year", "yoctogram", "yoctometer",
	"yoctometerscubed", "yoctometerssquared", "yoctosecond", "yottagram", "yottameter",
	"yottameterscubed", "yottameterssquared", "yottasecond", "zeptogram", "zeptometer",
	"zeptometerscubed", "zeptometerssquared", "zeptosecond", "zettagram", "zettameter",
	"zettameterscubed", "zettameterssquared", "zettasecond"
};
constexpr const int unitIndices[numUnits] = {
	52, 0, 53, 54, 56, 55, 57, 58, 59, 61, 2, 1, 63, 62, 64, 66, 65, 67, 3, 4, 68, 5, 6, 8,
	7, 9, 76, 69, 71, 73, 72, 74, 70, 75, 11, 12, 14, 13, 15, 77, 83, 78, 79, 80, 81, 82,
	10, 85, 86, 84, 87, 16, 88, 90, 94, 92, 91, 89, 95, 93, 98, 17, 102, 103, 104, 105, 19,
	20, 22, 21, 23, 99, 107, 100, 101, 106, 118, 142, 143, 144, 146, 145, 147, 110, 109,
	116, 112, 108, 111, 113, 115, 114, 117, 18, 119, 120, 121, 123, 122, 125, 124, 24, 25,
	126, 26, 27, 29, 28, 30, 128, 129, 131, 130, 132, 133, 97, 96, 127, 134, 31, 135, 136,
	32, 60, 138, 141, 33, 34, 36, 35, 37, 139, 137, 140, 39, 40, 38, 41, 148, 149, 154, 150,
	151, 153, 152, 155, 42, 43, 45, 44, 46, 156, 157, 159, 158, 160, 47, 48, 50, 49, 51
};
constexpr const char * unitAbbreviations[numUnits] = {
	"AU", "CD", "CG", "Dy", "EV", "Eg", "Em", "Em^2", "Em^3", "Es", "G", "Gg", "Gm", "Gm^2",
	"Gm^3", "Gs", "J", "L", "M", "Mg", "Mm", "Mm^2", "Mm^3", "Ms", "N", "Nm", "Pg", "Pm",
	"Pm^2", "Pm^3", "Ps", "Ry", "SM", "Tg", "Tm", "Tm^2", "Tm^3", "Ts", "UAM", "UKG", "UKT",
	"USG", "Yg", "Ym", "Ym^2", "Ym^3", "Ys", "Zg", "Zm", "Zm^2", "Zm^3", "Zs", "ac", "ag",
	"am", "am^2", "am^3", "as", "bn", "btu", "c", "cal", "cen", "cm", "cp", "dcm", "dec",
	"dm", "erg", "fg", "floz", "fm", "fm^2", "fm^3", "fs", "ft", "fth", "g", "g*m",
	"g*m/s^2", "g*m^2", "g*m^2/s^2", "g/s^2", "gF", "h", "hec", "hm", "in", "kg", "klbF",
	"km", "km^2", "km^3", "knt", "kph", "ks", "lb", "lbF", "ly", "m", "m/s", "m/s^2", "mE",
	"mMu", "mNt", "mPt", "m^2", "m^3", "mg", "mi", "mil", "ml", "mln", "mm", "mm^2", "mm^3",
	"mph", "ms", "mt", "mth", "ng", "nm", "nm^2", "nm^3", "nmi", "ns", "oz", "pdl", "pg",
	"pm", "pm^2", "pm^3", "ps", "pt", "qt", "s", "s^2", "t", "tbsp", "thm", "toz", "tsp",
	"ug", "ul", "um", "um^2", "um^3", "us", "wk", "yd", "yg", "ym", "ym^2", "ym^3", "yr",
	"ys", "zg", "zm", "zm^2", "zm^3", "zs"
};
constexpr const UnitType unitTypes[numUnits] = {
	DISTANCE, MASS, VOLUME, FORCE, ENERGY, MASS, DISTANCE, AREA, VOLUME, TIME, ACCELERATION,
	MASS, DISTANCE, AREA, VOLUME, TIME, ENERGY, VOLUME, TIME, MASS, DISTANCE, AREA, VOLUME,
	TIME, FORCE, ENERGY, MASS, DISTANCE, AREA, VOLUME, TIME, ENERGY, MASS, MASS, DISTANCE,
	AREA, VOLUME, TIME, MASS, VOLUME, MASS, VOLUME, MASS, DISTANCE, AREA, VOLUME, TIME,
	MASS, DISTANCE, AREA, VOLUME, TIME, AREA, MASS, DISTANCE, AREA, VOLUME, TIME, AREA,
	ENERGY, SPEED, ENERGY, TIME, DISTANCE, VOLUME, DISTANCE, TIME, DISTANCE, ENERGY, MASS,
	VOLUME, DISTANCE, AREA, VOLUME, TIME, DISTANCE, DISTANCE, MASS, MASSDISTANCE, FORCE,
	MASSAREA, ENERGY, MASSPERTIMESQUARED, FORCE, TIME, AREA, DISTANCE, DISTANCE, MASS,
	FORCE, DISTANCE, AREA, VOLUME, SPEED, SPEED, TIME, MASS, FORCE, DISTANCE, DISTANCE,
	SPEED, ACCELERATION, MASS, MASS, MASS, MASS, AREA, VOLUME, MASS, DISTANCE, DISTANCE,
	VOLUME, TIME, DISTANCE, AREA, VOLUME, SPEED, TIME, MASS, TIME, MASS, DISTANCE, AREA,
	VOLUME, DISTANCE, TIME, MASS, FORCE, MASS, DISTANCE, AREA, VOLUME, TIME, VOLUME, VOLUME,
	TIME, TIMESQUARED, MASS, VOLUME, ENERGY, MASS, VOLUME, MASS, VOLUME, DISTANCE, AREA,
	VOLUME, TIME, TIME, DISTANCE, MASS, DISTANCE, AREA, VOLUME, TIME, TIME, MASS, DISTANCE,
	AREA, VOLUME, TIME
};
constexpr const double unitConversions[numUnits] = {
	GSL_CONST_MKSA_ASTRONOMICAL_UNIT, GSL_CONST_MKSA_CARAT*1000.0,
	GSL_CONST_MKSA_CANADIAN_GALLON, GSL_CONST_MKSA_DYNE*1000.0,
	GSL_CONST_MKSA_ELECTRON_VOLT*1000.0, GSL_CONST_NUM_EXA, GSL_CONST_NUM_EXA,
	GSL_CONST_NUM_EXA, GSL_CONST_NUM_EXA, GSL_CONST_NUM_EXA, GSL_CONST_MKSA_GRAV_ACCEL,
	GSL_CONST_NUM_GIGA, GSL_CONST_NUM_GIGA, GSL_CONST_NUM_GIGA, GSL_CONST_NUM_GIGA,
	GSL_CONST_NUM_GIGA, GSL_CONST_MKSA_JOULE*1000.0, GSL_CONST_MKSA_LITER,
	GSL_CONST_MKSA_MINUTE, GSL_CONST_NUM_MEGA, GSL_CONST_NUM_MEGA, GSL_CONST_NUM_MEGA,
	GSL_CONST_NUM_MEGA, GSL_CONST_NUM_MEGA, GSL_CONST_MKSA_NEWTON*1000.0, 1000,
	GSL_CONST_NUM_PETA, GSL_CONST_NUM_PETA, GSL_CONST_NUM_PETA, GSL_CONST_NUM_PETA,
	GSL_CONST_NUM_PETA, GSL_CONST_MKSA_RYDBERG*1000.0, GSL_CONST_MKSA_SOLAR_MASS*1000.0,
	GSL_CONST_NUM_TERA, GSL_CONST_NUM_TERA, GSL_CONST_NUM_TERA, GSL_CONST_NUM_TERA,
	GSL_CONST_NUM_TERA, GSL_CONST_MKSA_UNIFIED_ATOMIC_MASS*1000.0, GSL_CONST_MKSA_UK_GALLON,
	GSL_CONST_MKSA_UK_TON*1000.0, GSL_CONST_MKSA_US_GALLON, GSL_CONST_NUM_YOTTA,
	GSL_CONST_NUM_YOTTA, GSL_CONST_NUM_YOTTA, GSL_CONST_NUM_YOTTA, GSL_CONST_NUM_YOTTA,
	GSL_CONST_NUM_ZETTA, GSL_CONST_NUM_ZETTA, GSL_CONST_NUM_ZETTA, GSL_CONST_NUM_ZETTA,
	GSL_CONST_NUM_ZETTA, GSL_CONST_MKSA_ACRE, GSL_CONST_NUM_ATTO, GSL_CONST_NUM_ATTO,
	GSL_CONST_NUM_ATTO, GSL_CONST_NUM_ATTO, GSL_CONST_NUM_ATTO, GSL_CONST_MKSA_BARN,
	GSL_CONST_MKSA_BTU*1000.0, GSL_CONST_MKSA_SPEED_OF_LIGHT, GSL_CONST_MKSA_CALORIE*1000.0,
	3153600000, 1e-2, GSL_CONST_MKSA_CUP, 1e1, 315360000, 1e-1, GSL_CONST_MKSA_ERG*1000.0,
	GSL_CONST_NUM_FEMTO, GSL_CONST_MKSA_FLUID_OUNCE, GSL_CONST_NUM_FEMTO,
	GSL_CONST_NUM_FEMTO, GSL_CONST_NUM_FEMTO, GSL_CONST_NUM_FEMTO, GSL_CONST_MKSA_FOOT,
	GSL_CONST_MKSA_FATHOM, 1, 1, 1, 1, 1, 1, GSL_CONST_MKSA_GRAM_FORCE*1000.0,
	GSL_CONST_MKSA_HOUR, GSL_CONST_MKSA_HECTARE, 1e2, GSL_CONST_MKSA_INCH,
	GSL_CONST_NUM_KILO, GSL_CONST_MKSA_KILOPOUND_FORCE*1000.0, GSL_CONST_NUM_KILO,
	GSL_CONST_NUM_KILO, GSL_CONST_NUM_KILO, GSL_CONST_MKSA_KNOT,
	GSL_CONST_MKSA_KILOMETERS_PER_HOUR, GSL_CONST_NUM_KILO,
	GSL_CONST_MKSA_POUND_MASS*1000.0, GSL_CONST_MKSA_POUND_FORCE*1000.0,
	GSL_CONST_MKSA_LIGHT_YEAR, 1, 1, 1, GSL_CONST_MKSA_MASS_ELECTRON*1000.0,
	GSL_CONST_MKSA_MASS_MUON*1000.0, GSL_CONST_MKSA_MASS_NEUTRON*1000.0,
	GSL_CONST_MKSA_MASS_PROTON*1000.0, 1, 1, GSL_CONST_NUM_MILLI, GSL_CONST_MKSA_MILE,
	GSL_CONST_MKSA_MIL, 1e-6, 31536000000, GSL_CONST_NUM_MILLI, GSL_CONST_NUM_MILLI,
	GSL_CONST_NUM_MILLI, GSL_CONST_MKSA_MILES_PER_HOUR, GSL_CONST_NUM_MILLI,
	GSL_CONST_MKSA_METRIC_TON*1000.0, 2628288, GSL_CONST_NUM_NANO, GSL_CONST_NUM_NANO,
	GSL_CONST_NUM_NANO, GSL_CONST_NUM_NANO, GSL_CONST_MKSA_NAUTICAL_MILE,
	GSL_CONST_NUM_NANO, GSL_CONST_MKSA_OUNCE_MASS*1000.0, GSL_CONST_MKSA_POUNDAL*1000.0,
	GSL_CONST_NUM_PICO, GSL_CONST_NUM_PICO, GSL_CONST_NUM_PICO, GSL_CONST_NUM_PICO,
	GSL_CONST_NUM_PICO, GSL_CONST_MKSA_PINT, GSL_CONST_MKSA_QUART, 1, 1,
	GSL_CONST_MKSA_TON*1000.0, GSL_CONST_MKSA_TABLESPOON, GSL_CONST_MKSA_THERM*1000.0,
	GSL_CONST_MKSA_TROY_OUNCE*1000.0, GSL_CONST_MKSA_TEASPOON, GSL_CONST_NUM_MICRO, 1e-9,
	GSL_CONST_NUM_MICRO, GSL_CONST_NUM_MICRO, GSL_CONST_NUM_MICRO, GSL_CONST_NUM_MICRO,
	GSL_CONST_MKSA_WEEK, GSL_CONST_MKSA_YARD, GSL_CONST_NUM_YOCTO, GSL_CONST_NUM_YOCTO,
	GSL_CONST_NUM_YOCTO, GSL_CONST_NUM_YOCTO, 31536000, GSL_CONST_NUM_YOCTO,
	GSL_CONST_NUM_ZEPTO, GSL_CONST_NUM_ZEPTO, GSL_CONST_NUM_ZEPTO, GSL_CONST_NUM_ZEPTO,
	GSL_CONST_NUM_ZEPTO
};

/*
Returns index of the unit in the unitNames array.

Uses binary search under the hood to search for the index.

Parameters
----------
name: The name of the unit

Returns
-------
The index or -1 if the provided name is not a unit.
*/
CONSTEXPR_BINARY_SEARCH(getUnitIndex, unitNames, numUnits)

CONSTEXPR_BINARY_SEARCH(getAbbrIndex, unitAbbreviations, numUnits)


constexpr UnitType getUnitType(const char* name){
    int index = getUnitIndex(name);
    if (index != -1){
		return NONE;
	}
	return unitTypes[index];
}
inline UnitType getUnitType(const std::string& name){
    int index = getUnitIndex(name.c_str());
    if (index != -1){
		return NONE;
	}
	return unitTypes[index];
}
inline UnitType getUnitType(int index){
    if (index < 0 || index >= numUnits){
		return NONE;
	}
	return unitTypes[index];
}

constexpr double getUnitConversion(const char* name){
    int index = getUnitIndex(name);
    if (index != -1){
		return NONE;
	}
	return unitConversions[index];
}
inline double getUnitConversion(const std::string& name){
    int index = getUnitIndex(name.c_str());
    if (index != -1){
		return NONE;
	}
	return unitConversions[index];
}
inline double getUnitConversion(int index){
    if (index < 0 || index >= numUnits){
		return NONE;
	}
	return unitConversions[index];
}
