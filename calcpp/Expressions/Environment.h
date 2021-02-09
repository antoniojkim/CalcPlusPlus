
#include <memory>
#include <unordered_map>

#include "Types.h"

namespace calcpp {
    class Expression;
    typedef std::shared_ptr<Expression> expression;

    class Environment {
        std::unordered_map<std::string, expression> map;
        const Environment* parentEnv;

      protected:
        Environment();

      public:
        Environment(const Environment* parentEnv = nullptr);
        Environment(const Environment& parentEnv);

        expression operator[](const std::string& name) const;

        void set(const std::string& name, const expression e);
        void set(const expression var, const expression e);
        void set(const std::string& name, const Double val);
        void set(const expression var, const Double val);
        void remove(const std::string& name);
    };

    extern const Environment defaultEnv;

}  // namespace calcpp
