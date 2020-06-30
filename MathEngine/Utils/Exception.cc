
#include "Exception.h"

std::ostream& operator<<(std::ostream& out, const Exception& e){
    return out << e.msg;
}
