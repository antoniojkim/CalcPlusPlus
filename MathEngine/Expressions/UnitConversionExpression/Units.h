#pragma once

/***************************************************
 *************** Auto-Generated File ***************
 ***************************************************/

#include <cstring>
#include <string>

#include <gsl/gsl_const_mksa.h>
#include <gsl/gsl_const_num.h>

enum UnitType {
	NONE,
	DISTANCE,
	TIME,
	AREA,
	VOLUME,
	MASS
};

constexpr const int numUnits = 127;
constexpr const char* unitNames[numUnits] = {
	"acre", "attogram", "attometer", "attometerscubed", "attometerssquared", "attosecond",
	"barn", "canadian_gallon", "carat", "centimeter", "century", "cup", "decade",
	"decameter", "decimeter", "exagram", "exameter", "exameterscubed", "exameterssquared",
	"exasecond", "fathom", "femtogram", "femtometer", "femtometerscubed",
	"femtometerssquared", "femtosecond", "fluid_ounce", "foot", "gigagram", "gigameter",
	"gigameterscubed", "gigameterssquared", "gigasecond", "gram", "hectare", "hectometer",
	"hour", "inch", "kilogram", "kilometer", "kilometerscubed", "kilometerssquared",
	"kilosecond", "liter", "megagram", "megameter", "megameterscubed", "megameterssquared",
	"megasecond", "meter", "meterscubed", "meterssquared", "metric_ton", "microgram",
	"microliter", "micrometer", "micrometerscubed", "micrometerssquared", "microsecond",
	"mil", "mile", "millenium", "milligram", "milliliter", "millimeter", "millimeterscubed",
	"millimeterssquared", "millisecond", "minute", "month", "nanogram", "nanometer",
	"nanometerscubed", "nanometerssquared", "nanosecond", "nautical_mile", "ounce",
	"petagram", "petameter", "petameterscubed", "petameterssquared", "petasecond",
	"picogram", "picometer", "picometerscubed", "picometerssquared", "picosecond", "pint",
	"pound", "quart", "second", "tablespoon", "teaspoon", "teragram", "terameter",
	"terameterscubed", "terameterssquared", "terasecond", "ton", "troy_ounce", "uk_gallon",
	"uk_ton", "unified_atomic_mass", "us_gallon", "week", "yard", "year", "yoctogram",
	"yoctometer", "yoctometerscubed", "yoctometerssquared", "yoctosecond", "yottagram",
	"yottameter", "yottameterscubed", "yottameterssquared", "yottasecond", "zeptogram",
	"zeptometer", "zeptometerscubed", "zeptometerssquared", "zeptosecond", "zettagram",
	"zettameter", "zettameterscubed", "zettameterssquared", "zettasecond"
};
constexpr const int unitIndices[numUnits] = {
	42, 43, 44, 46, 45, 47, 48, 1, 0, 50, 49, 51, 53, 52, 54, 2, 3, 5, 4, 6, 62, 55, 57, 59,
	58, 60, 56, 61, 7, 8, 10, 9, 11, 63, 64, 65, 66, 67, 68, 69, 71, 70, 72, 12, 13, 14, 16,
	15, 17, 74, 76, 75, 87, 108, 109, 110, 112, 111, 113, 79, 78, 82, 77, 81, 83, 85, 84,
	86, 80, 88, 89, 90, 92, 91, 94, 93, 95, 18, 19, 21, 20, 22, 96, 97, 99, 98, 100, 101,
	73, 102, 103, 105, 107, 23, 24, 26, 25, 27, 104, 106, 29, 30, 28, 31, 114, 115, 120,
	116, 117, 119, 118, 121, 32, 33, 35, 34, 36, 122, 123, 125, 124, 126, 37, 38, 40, 39, 41
};
constexpr const char * unitAbbreviations[numUnits] = {
	"CD", "CG", "Eg", "Em", "Em^2", "Em^3", "Es", "Gg", "Gm", "Gm^2", "Gm^3", "Gs", "L",
	"Mg", "Mm", "Mm^2", "Mm^3", "Ms", "Pg", "Pm", "Pm^2", "Pm^3", "Ps", "Tg", "Tm", "Tm^2",
	"Tm^3", "Ts", "UAM", "UKG", "UKT", "USG", "Yg", "Ym", "Ym^2", "Ym^3", "Ys", "Zg", "Zm",
	"Zm^2", "Zm^3", "Zs", "ac", "ag", "am", "am^2", "am^3", "as", "bn", "cen", "cm", "cp",
	"dcm", "dec", "dm", "fg", "floz", "fm", "fm^2", "fm^3", "fs", "ft", "fth", "g", "hec",
	"hm", "hr", "in", "kg", "km", "km^2", "km^3", "ks", "lb", "m", "m^2", "m^3", "mg", "mi",
	"mil", "min", "ml", "mln", "mm", "mm^2", "mm^3", "ms", "mt", "mth", "ng", "nm", "nm^2",
	"nm^3", "nmi", "ns", "oz", "pg", "pm", "pm^2", "pm^3", "ps", "pt", "qt", "s", "t",
	"tbsp", "toz", "tsp", "ug", "ul", "um", "um^2", "um^3", "us", "wk", "yd", "yg", "ym",
	"ym^2", "ym^3", "yr", "ys", "zg", "zm", "zm^2", "zm^3", "zs"
};
constexpr const UnitType unitTypes[numUnits] = {
	MASS, VOLUME, MASS, DISTANCE, AREA, VOLUME, TIME, MASS, DISTANCE, AREA, VOLUME, TIME,
	VOLUME, MASS, DISTANCE, AREA, VOLUME, TIME, MASS, DISTANCE, AREA, VOLUME, TIME, MASS,
	DISTANCE, AREA, VOLUME, TIME, MASS, VOLUME, MASS, VOLUME, MASS, DISTANCE, AREA, VOLUME,
	TIME, MASS, DISTANCE, AREA, VOLUME, TIME, AREA, MASS, DISTANCE, AREA, VOLUME, TIME,
	AREA, TIME, DISTANCE, VOLUME, DISTANCE, TIME, DISTANCE, MASS, VOLUME, DISTANCE, AREA,
	VOLUME, TIME, DISTANCE, DISTANCE, MASS, AREA, DISTANCE, TIME, DISTANCE, MASS, DISTANCE,
	AREA, VOLUME, TIME, MASS, DISTANCE, AREA, VOLUME, MASS, DISTANCE, DISTANCE, TIME,
	VOLUME, TIME, DISTANCE, AREA, VOLUME, TIME, MASS, TIME, MASS, DISTANCE, AREA, VOLUME,
	DISTANCE, TIME, MASS, MASS, DISTANCE, AREA, VOLUME, TIME, VOLUME, VOLUME, TIME, MASS,
	VOLUME, MASS, VOLUME, MASS, VOLUME, DISTANCE, AREA, VOLUME, TIME, TIME, DISTANCE, MASS,
	DISTANCE, AREA, VOLUME, TIME, TIME, MASS, DISTANCE, AREA, VOLUME, TIME
};
constexpr const double unitConversions[numUnits] = {
	GSL_CONST_MKSA_CARAT, GSL_CONST_MKSA_CANADIAN_GALLON, GSL_CONST_NUM_EXA,
	GSL_CONST_NUM_EXA, GSL_CONST_NUM_EXA, GSL_CONST_NUM_EXA, GSL_CONST_NUM_EXA,
	GSL_CONST_NUM_GIGA, GSL_CONST_NUM_GIGA, GSL_CONST_NUM_GIGA, GSL_CONST_NUM_GIGA,
	GSL_CONST_NUM_GIGA, GSL_CONST_MKSA_LITER, GSL_CONST_NUM_MEGA, GSL_CONST_NUM_MEGA,
	GSL_CONST_NUM_MEGA, GSL_CONST_NUM_MEGA, GSL_CONST_NUM_MEGA, GSL_CONST_NUM_PETA,
	GSL_CONST_NUM_PETA, GSL_CONST_NUM_PETA, GSL_CONST_NUM_PETA, GSL_CONST_NUM_PETA,
	GSL_CONST_NUM_TERA, GSL_CONST_NUM_TERA, GSL_CONST_NUM_TERA, GSL_CONST_NUM_TERA,
	GSL_CONST_NUM_TERA, GSL_CONST_MKSA_UNIFIED_ATOMIC_MASS, GSL_CONST_MKSA_UK_GALLON,
	GSL_CONST_MKSA_UK_TON*1e3, GSL_CONST_MKSA_US_GALLON, GSL_CONST_NUM_YOTTA,
	GSL_CONST_NUM_YOTTA, GSL_CONST_NUM_YOTTA, GSL_CONST_NUM_YOTTA, GSL_CONST_NUM_YOTTA,
	GSL_CONST_NUM_ZETTA, GSL_CONST_NUM_ZETTA, GSL_CONST_NUM_ZETTA, GSL_CONST_NUM_ZETTA,
	GSL_CONST_NUM_ZETTA, GSL_CONST_MKSA_ACRE, GSL_CONST_NUM_ATTO, GSL_CONST_NUM_ATTO,
	GSL_CONST_NUM_ATTO, GSL_CONST_NUM_ATTO, GSL_CONST_NUM_ATTO, GSL_CONST_MKSA_BARN,
	3153600000, 1e-2, GSL_CONST_MKSA_CUP, 1e1, 315360000, 1e-1, GSL_CONST_NUM_FEMTO,
	GSL_CONST_MKSA_FLUID_OUNCE, GSL_CONST_NUM_FEMTO, GSL_CONST_NUM_FEMTO,
	GSL_CONST_NUM_FEMTO, GSL_CONST_NUM_FEMTO, GSL_CONST_MKSA_FOOT, GSL_CONST_MKSA_FATHOM, 1,
	GSL_CONST_MKSA_HECTARE, 1e2, GSL_CONST_MKSA_HOUR, GSL_CONST_MKSA_INCH,
	GSL_CONST_NUM_KILO, GSL_CONST_NUM_KILO, GSL_CONST_NUM_KILO, GSL_CONST_NUM_KILO,
	GSL_CONST_NUM_KILO, GSL_CONST_MKSA_POUND_MASS*1e3, 1, 1, 1, GSL_CONST_NUM_MILLI,
	GSL_CONST_MKSA_MILE, GSL_CONST_MKSA_MIL, GSL_CONST_MKSA_MINUTE, 1e-6, 31536000000,
	GSL_CONST_NUM_MILLI, GSL_CONST_NUM_MILLI, GSL_CONST_NUM_MILLI, GSL_CONST_NUM_MILLI,
	GSL_CONST_MKSA_METRIC_TON*1e3, 2628288, GSL_CONST_NUM_NANO, GSL_CONST_NUM_NANO,
	GSL_CONST_NUM_NANO, GSL_CONST_NUM_NANO, GSL_CONST_MKSA_NAUTICAL_MILE,
	GSL_CONST_NUM_NANO, GSL_CONST_MKSA_OUNCE_MASS*1e3, GSL_CONST_NUM_PICO,
	GSL_CONST_NUM_PICO, GSL_CONST_NUM_PICO, GSL_CONST_NUM_PICO, GSL_CONST_NUM_PICO,
	GSL_CONST_MKSA_PINT, GSL_CONST_MKSA_QUART, 1, GSL_CONST_MKSA_TON*1e3,
	GSL_CONST_MKSA_TABLESPOON, GSL_CONST_MKSA_TROY_OUNCE*1e3, GSL_CONST_MKSA_TEASPOON,
	GSL_CONST_NUM_MICRO, 1e-9, GSL_CONST_NUM_MICRO, GSL_CONST_NUM_MICRO,
	GSL_CONST_NUM_MICRO, GSL_CONST_NUM_MICRO, GSL_CONST_MKSA_WEEK, GSL_CONST_MKSA_YARD,
	GSL_CONST_NUM_YOCTO, GSL_CONST_NUM_YOCTO, GSL_CONST_NUM_YOCTO, GSL_CONST_NUM_YOCTO,
	31536000, GSL_CONST_NUM_YOCTO, GSL_CONST_NUM_ZEPTO, GSL_CONST_NUM_ZEPTO,
	GSL_CONST_NUM_ZEPTO, GSL_CONST_NUM_ZEPTO, GSL_CONST_NUM_ZEPTO
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
constexpr int getUnitIndex(const char* name){
    int low = 0;
    int high = numUnits - 1;
    while (true){
        if (low > high){
            return -1;
        }

        int mid = (low + high) / 2;
        int cmp = std::strcmp(name, unitNames[mid]);
        if (cmp == 0){
            return unitIndices[mid];
        }
        else if (cmp < 0){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return -1;
}
inline int getUnitIndex(const std::string& name){
    return getUnitIndex(name.c_str());
}
constexpr int getAbbrIndex(const char* name){
    int low = 0;
    int high = numUnits - 1;
    while (true){
        if (low > high){
            return -1;
        }

        int mid = (low + high) / 2;
        int cmp = std::strcmp(name, unitAbbreviations[mid]);
        if (cmp == 0){
            return mid;
        }
        else if (cmp < 0){
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return -1;
}
inline int getAbbrIndex(const std::string& name){
    return getAbbrIndex(name.c_str());
}


constexpr UnitType getUnitType(const char* name){
    int index = getUnitIndex(name);
    if (index != -1){
		return NONE;
	}
	return unitTypes[index];
}
inline UnitType getUnitType(const std::string& name){
    int index = getUnitIndex(name);
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

constexpr UnitType getUnitType(const char* name){
    int index = getUnitIndex(name);
    if (index != -1){
		return NONE;
	}
	return unitTypes[index];
}
inline UnitType getUnitType(const std::string& name){
    int index = getUnitIndex(name);
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
