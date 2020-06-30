#pragma once

#define BINARY_SEARCH_INDEX_OF(ARRAY, LENGTH)               \
    constexpr int indexOf(const char* name){                \
        int low = 0;                                        \
        int high = LENGTH - 1;                              \
        while (true){                                       \
            if (low > high){                                \
                return -1;                                  \
            }                                               \
            int mid = (low + high) / 2;                     \
            int cmp = std::strcmp(name, ARRAY[mid]);        \
            if (cmp == 0){                                  \
                return mid;                                 \
            }                                               \
            else if (cmp < 0){                              \
                high = mid-1;                               \
            }                                               \
            else{                                           \
                low = mid+1;                                \
            }                                               \
        }                                                   \
        return -1;                                          \
    }                                                       \
    inline int indexOf(const std::string& name){            \
        return indexOf(name.c_str());                       \
    }
