#pragma once

constexpr int compare_string(char const * a, char const * b) {
    if (*a == *b){
        if (*a == '\0'){
            return 0;
        }
        else {
            return compare_string(a + 1, b + 1);
        }
    }
    else if (*a < *b){
        return -1;
    }
    return 1;
}

#define CONSTEXPR_BINARY_SEARCH(FNAME, ARRAY, LENGTH)       \
    constexpr int FNAME(const char* name){                  \
        int low = 0;                                        \
        int high = LENGTH - 1;                              \
        while (true){                                       \
            if (low > high){                                \
                return -1;                                  \
            }                                               \
            int mid = (low + high) / 2;                     \
            int cmp = compare_string(name, ARRAY[mid]);     \
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
    inline int FNAME(const std::string& name){              \
        return FNAME(name.c_str());                         \
    }

#define BINARY_SEARCH_INDEX_OF(ARRAY, LENGTH) \
    CONSTEXPR_BINARY_SEARCH(indexOf, ARRAY, LENGTH)
