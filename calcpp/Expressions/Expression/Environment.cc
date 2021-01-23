#include "../Environment.h"
#include "../Expression.h"

using namespace std;

namespace calcpp {

    Environment::Environment() {}

    expression Environment::operator[](const string& name) const { return map[name]; }

    void Environment::set(const string& name, expression e) { map[name] = e; }
    void Environment::remove(const string& name) { map.erase(name); }

}  // namespace calcpp
