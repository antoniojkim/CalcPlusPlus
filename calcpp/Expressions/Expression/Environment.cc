#include "../Environment.h"
#include "../../Utils/Exception.h"
#include "../Expression.h"
#include "../ExpressionFunctions.h"

using namespace std;

namespace calcpp {

    Environment::Environment() {}
    Environment::Environment(const Environment const* parentEnv) :
        parentEnv{parentEnv ? parentEnv : defaultEnv} {}
    Environment::Environment(const Environment& parentEnv) : parentEnv{&parentEnv} {}

    expression Environment::operator[](const string& name) const {
        if (map.count(name) != 0) { return map[name]; }
        return (*parentEnv)[name];
    }

    void Environment::set(const string& name, const expression e) { map[name] = e; }
    void Environment::set(const expression var, const expression e) {
        if (var != Type::VAR) { THROW_ERROR("Cannot set an non variable expression"); }
        map[var->repr()] = e;
    }
    void Environment::set(const string& name, const Double val) {
        map[name] = num(val);
    }
    void Environment::set(const expression var, const Double val) {
        if (var != Type::VAR) { THROW_ERROR("Cannot set an non variable expression"); }
        map[var->repr()] = num(val);
    }
    void Environment::remove(const string& name) { map.erase(name); }

}  // namespace calcpp
