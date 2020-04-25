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
