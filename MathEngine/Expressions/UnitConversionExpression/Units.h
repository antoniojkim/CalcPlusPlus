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
	TIMESQUARED,
	SPEED,
	ACCELERATION,
	AREA,
	VOLUME,
	MASS
};

constexpr const int numUnits = 140;
constexpr const char* unitNames[numUnits] = {
	"acre", "attogram", "attometer", "attometerscubed", "attometerssquared", "attosecond",
	"barn", "canadian_gallon", "carat", "centimeter", "century", "cup", "decade",
	"decameter", "decimeter", "exagram", "exameter", "exameterscubed", "exameterssquared",
	"exasecond", "fathom", "femtogram", "femtometer", "femtometerscubed",
	"femtometerssquared", "femtosecond", "fluid_ounce", "foot", "gigagram", "gigameter",
	"gigameterscubed", "gigameterssquared", "gigasecond", "gram", "grav_accel", "hectare",
	"hectometer", "hour", "inch", "kilogram", "kilometer", "kilometers_per_hour",
	"kilometerscubed", "kilometerssquared", "kilosecond", "knot", "liter", "mass_electron",
	"mass_muon", "mass_neutron", "mass_proton", "megagram", "megameter", "megameterscubed",
	"megameterssquared", "megasecond", "meter", "meterscubed", "meterspersecond",
	"meterspersecondsquared", "meterssquared", "metric_ton", "microgram", "microliter",
	"micrometer", "micrometerscubed", "micrometerssquared", "microsecond", "mil", "mile",
	"miles_per_hour", "millenium", "milligram", "milliliter", "millimeter",
	"millimeterscubed", "millimeterssquared", "millisecond", "minute", "month", "nanogram",
	"nanometer", "nanometerscubed", "nanometerssquared", "nanosecond", "nautical_mile",
	"ounce_mass", "petagram", "petameter", "petameterscubed", "petameterssquared",
	"petasecond", "picogram", "picometer", "picometerscubed", "picometerssquared",
	"picosecond", "pint", "pound_mass", "quart", "second", "secondsquared", "solar_mass",
	"speed_of_light", "tablespoon", "teaspoon", "teragram", "terameter", "terameterscubed",
	"terameterssquared", "terasecond", "ton", "troy_ounce", "uk_gallon", "uk_ton",
	"unified_atomic_mass", "us_gallon", "week", "yard", "year", "yoctogram", "yoctometer",
	"yoctometerscubed", "yoctometerssquared", "yoctosecond", "yottagram", "yottameter",
	"yottameterscubed", "yottameterssquared", "yottasecond", "zeptogram", "zeptometer",
	"zeptometerscubed", "zeptometerssquared", "zeptosecond", "zettagram", "zettameter",
	"zettameterscubed", "zettameterssquared", "zettasecond"
};
constexpr const int unitIndices[numUnits] = {
	45, 46, 47, 49, 48, 50, 51, 1, 0, 54, 53, 55, 57, 56, 58, 2, 3, 5, 4, 6, 66, 59, 61, 63,
	62, 64, 60, 65, 8, 9, 11, 10, 12, 67, 7, 69, 70, 68, 71, 72, 73, 77, 75, 74, 78, 76, 13,
	83, 84, 85, 86, 15, 16, 18, 17, 19, 80, 88, 81, 82, 87, 99, 121, 122, 123, 125, 124,
	126, 91, 90, 97, 93, 89, 92, 94, 96, 95, 98, 14, 100, 101, 102, 104, 103, 106, 105, 107,
	20, 21, 23, 22, 24, 108, 109, 111, 110, 112, 113, 79, 114, 115, 116, 25, 52, 118, 120,
	26, 27, 29, 28, 30, 117, 119, 32, 33, 31, 34, 127, 128, 133, 129, 130, 132, 131, 134,
	35, 36, 38, 37, 39, 135, 136, 138, 137, 139, 40, 41, 43, 42, 44
};
constexpr const char * unitAbbreviations[numUnits] = {
	"CD", "CG", "Eg", "Em", "Em^2", "Em^3", "Es", "G", "Gg", "Gm", "Gm^2", "Gm^3", "Gs",
	"L", "M", "Mg", "Mm", "Mm^2", "Mm^3", "Ms", "Pg", "Pm", "Pm^2", "Pm^3", "Ps", "SM",
	"Tg", "Tm", "Tm^2", "Tm^3", "Ts", "UAM", "UKG", "UKT", "USG", "Yg", "Ym", "Ym^2",
	"Ym^3", "Ys", "Zg", "Zm", "Zm^2", "Zm^3", "Zs", "ac", "ag", "am", "am^2", "am^3", "as",
	"bn", "c", "cen", "cm", "cp", "dcm", "dec", "dm", "fg", "floz", "fm", "fm^2", "fm^3",
	"fs", "ft", "fth", "g", "h", "hec", "hm", "in", "kg", "km", "km^2", "km^3", "knt",
	"kph", "ks", "lb", "m", "m/s", "m/s^2", "mE", "mMu", "mNt", "mPt", "m^2", "m^3", "mg",
	"mi", "mil", "ml", "mln", "mm", "mm^2", "mm^3", "mph", "ms", "mt", "mth", "ng", "nm",
	"nm^2", "nm^3", "nmi", "ns", "oz", "pg", "pm", "pm^2", "pm^3", "ps", "pt", "qt", "s",
	"s^2", "t", "tbsp", "toz", "tsp", "ug", "ul", "um", "um^2", "um^3", "us", "wk", "yd",
	"yg", "ym", "ym^2", "ym^3", "yr", "ys", "zg", "zm", "zm^2", "zm^3", "zs"
};
constexpr const UnitType unitTypes[numUnits] = {
	MASS, VOLUME, MASS, DISTANCE, AREA, VOLUME, TIME, ACCELERATION, MASS, DISTANCE, AREA,
	VOLUME, TIME, VOLUME, TIME, MASS, DISTANCE, AREA, VOLUME, TIME, MASS, DISTANCE, AREA,
	VOLUME, TIME, MASS, MASS, DISTANCE, AREA, VOLUME, TIME, MASS, VOLUME, MASS, VOLUME,
	MASS, DISTANCE, AREA, VOLUME, TIME, MASS, DISTANCE, AREA, VOLUME, TIME, AREA, MASS,
	DISTANCE, AREA, VOLUME, TIME, AREA, SPEED, TIME, DISTANCE, VOLUME, DISTANCE, TIME,
	DISTANCE, MASS, VOLUME, DISTANCE, AREA, VOLUME, TIME, DISTANCE, DISTANCE, MASS, TIME,
	AREA, DISTANCE, DISTANCE, MASS, DISTANCE, AREA, VOLUME, SPEED, SPEED, TIME, MASS,
	DISTANCE, SPEED, ACCELERATION, MASS, MASS, MASS, MASS, AREA, VOLUME, MASS, DISTANCE,
	DISTANCE, VOLUME, TIME, DISTANCE, AREA, VOLUME, SPEED, TIME, MASS, TIME, MASS, DISTANCE,
	AREA, VOLUME, DISTANCE, TIME, MASS, MASS, DISTANCE, AREA, VOLUME, TIME, VOLUME, VOLUME,
	TIME, TIMESQUARED, MASS, VOLUME, MASS, VOLUME, MASS, VOLUME, DISTANCE, AREA, VOLUME,
	TIME, TIME, DISTANCE, MASS, DISTANCE, AREA, VOLUME, TIME, TIME, MASS, DISTANCE, AREA,
	VOLUME, TIME
};
constexpr const double unitConversions[numUnits] = {
	GSL_CONST_MKSA_CARAT*1000.0, GSL_CONST_MKSA_CANADIAN_GALLON, GSL_CONST_NUM_EXA,
	GSL_CONST_NUM_EXA, GSL_CONST_NUM_EXA, GSL_CONST_NUM_EXA, GSL_CONST_NUM_EXA,
	GSL_CONST_MKSA_GRAV_ACCEL, GSL_CONST_NUM_GIGA, GSL_CONST_NUM_GIGA, GSL_CONST_NUM_GIGA,
	GSL_CONST_NUM_GIGA, GSL_CONST_NUM_GIGA, GSL_CONST_MKSA_LITER, GSL_CONST_MKSA_MINUTE,
	GSL_CONST_NUM_MEGA, GSL_CONST_NUM_MEGA, GSL_CONST_NUM_MEGA, GSL_CONST_NUM_MEGA,
	GSL_CONST_NUM_MEGA, GSL_CONST_NUM_PETA, GSL_CONST_NUM_PETA, GSL_CONST_NUM_PETA,
	GSL_CONST_NUM_PETA, GSL_CONST_NUM_PETA, GSL_CONST_MKSA_SOLAR_MASS*1000.0,
	GSL_CONST_NUM_TERA, GSL_CONST_NUM_TERA, GSL_CONST_NUM_TERA, GSL_CONST_NUM_TERA,
	GSL_CONST_NUM_TERA, GSL_CONST_MKSA_UNIFIED_ATOMIC_MASS*1000.0, GSL_CONST_MKSA_UK_GALLON,
	GSL_CONST_MKSA_UK_TON*1000.0, GSL_CONST_MKSA_US_GALLON, GSL_CONST_NUM_YOTTA,
	GSL_CONST_NUM_YOTTA, GSL_CONST_NUM_YOTTA, GSL_CONST_NUM_YOTTA, GSL_CONST_NUM_YOTTA,
	GSL_CONST_NUM_ZETTA, GSL_CONST_NUM_ZETTA, GSL_CONST_NUM_ZETTA, GSL_CONST_NUM_ZETTA,
	GSL_CONST_NUM_ZETTA, GSL_CONST_MKSA_ACRE, GSL_CONST_NUM_ATTO, GSL_CONST_NUM_ATTO,
	GSL_CONST_NUM_ATTO, GSL_CONST_NUM_ATTO, GSL_CONST_NUM_ATTO, GSL_CONST_MKSA_BARN,
	GSL_CONST_MKSA_SPEED_OF_LIGHT, 3153600000, 1e-2, GSL_CONST_MKSA_CUP, 1e1, 315360000,
	1e-1, GSL_CONST_NUM_FEMTO, GSL_CONST_MKSA_FLUID_OUNCE, GSL_CONST_NUM_FEMTO,
	GSL_CONST_NUM_FEMTO, GSL_CONST_NUM_FEMTO, GSL_CONST_NUM_FEMTO, GSL_CONST_MKSA_FOOT,
	GSL_CONST_MKSA_FATHOM, 1, GSL_CONST_MKSA_HOUR, GSL_CONST_MKSA_HECTARE, 1e2,
	GSL_CONST_MKSA_INCH, GSL_CONST_NUM_KILO, GSL_CONST_NUM_KILO, GSL_CONST_NUM_KILO,
	GSL_CONST_NUM_KILO, GSL_CONST_MKSA_KNOT, GSL_CONST_MKSA_KILOMETERS_PER_HOUR,
	GSL_CONST_NUM_KILO, GSL_CONST_MKSA_POUND_MASS*1000.0, 1, 1, 1,
	GSL_CONST_MKSA_MASS_ELECTRON*1000.0, GSL_CONST_MKSA_MASS_MUON*1000.0,
	GSL_CONST_MKSA_MASS_NEUTRON*1000.0, GSL_CONST_MKSA_MASS_PROTON*1000.0, 1, 1,
	GSL_CONST_NUM_MILLI, GSL_CONST_MKSA_MILE, GSL_CONST_MKSA_MIL, 1e-6, 31536000000,
	GSL_CONST_NUM_MILLI, GSL_CONST_NUM_MILLI, GSL_CONST_NUM_MILLI,
	GSL_CONST_MKSA_MILES_PER_HOUR, GSL_CONST_NUM_MILLI, GSL_CONST_MKSA_METRIC_TON*1000.0,
	2628288, GSL_CONST_NUM_NANO, GSL_CONST_NUM_NANO, GSL_CONST_NUM_NANO, GSL_CONST_NUM_NANO,
	GSL_CONST_MKSA_NAUTICAL_MILE, GSL_CONST_NUM_NANO, GSL_CONST_MKSA_OUNCE_MASS*1000.0,
	GSL_CONST_NUM_PICO, GSL_CONST_NUM_PICO, GSL_CONST_NUM_PICO, GSL_CONST_NUM_PICO,
	GSL_CONST_NUM_PICO, GSL_CONST_MKSA_PINT, GSL_CONST_MKSA_QUART, 1, 1,
	GSL_CONST_MKSA_TON*1000.0, GSL_CONST_MKSA_TABLESPOON, GSL_CONST_MKSA_TROY_OUNCE*1000.0,
	GSL_CONST_MKSA_TEASPOON, GSL_CONST_NUM_MICRO, 1e-9, GSL_CONST_NUM_MICRO,
	GSL_CONST_NUM_MICRO, GSL_CONST_NUM_MICRO, GSL_CONST_NUM_MICRO, GSL_CONST_MKSA_WEEK,
	GSL_CONST_MKSA_YARD, GSL_CONST_NUM_YOCTO, GSL_CONST_NUM_YOCTO, GSL_CONST_NUM_YOCTO,
	GSL_CONST_NUM_YOCTO, 31536000, GSL_CONST_NUM_YOCTO, GSL_CONST_NUM_ZEPTO,
	GSL_CONST_NUM_ZEPTO, GSL_CONST_NUM_ZEPTO, GSL_CONST_NUM_ZEPTO, GSL_CONST_NUM_ZEPTO
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

constexpr double getUnitConversion(const char* name){
    int index = getUnitIndex(name);
    if (index != -1){
		return NONE;
	}
	return unitConversions[index];
}
inline double getUnitConversion(const std::string& name){
    int index = getUnitIndex(name);
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
