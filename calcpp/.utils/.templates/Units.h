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
	{UnitTypes}
};

constexpr const int numUnits = {numUnits};
constexpr const char* unitNames[numUnits] = {
	{unitNames}
};
constexpr const int unitIndices[numUnits] = {
	{unitIndices}
};
constexpr const char * unitAbbreviations[numUnits] = {
	{unitAbbreviations}
};
constexpr const UnitType unitTypes[numUnits] = {
	{unitTypes}
};
constexpr const double unitConversions[numUnits] = {
	{unitConversions}
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
