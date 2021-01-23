
#include <memory>
#include <unordered_map>

namespace calcpp {
    class Expression;
    typedef std::shared_ptr<Expression> expression;

    class Environment {
        std::unordered_map<std::string, expression> map;

      public:
        Environment();

        expression operator[](const std::string& name) const;

        void set(const std::string& name, expression e);
        void remove(const std::string& name);
    };

    extern const Environment defaultEnv;

}  // namespace calcpp
