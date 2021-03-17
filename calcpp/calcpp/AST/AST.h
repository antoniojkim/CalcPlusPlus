#pragma once

#include <memory>
#include <ostream>

namespace calcpp {
    class AbstractSyntaxTree;

    typedef std::shared_ptr<AbstractSyntaxTree> AST;

    /*
      Base Abstract Syntax Tree
     */
    class AbstractSyntaxTree: std::enable_shared_from_this<AbstractSyntaxTree> {
      public:
        virtual ~AbstractSyntaxTree() {}

        virtual std::ostream& repr(std::ostream& out) const = 0;
    };

#define REGISTER_AST(ASTName)                                                          \
    template<typename... Args>                                                         \
    static AST construct(Args&&... args) {                                             \
        return std::shared_ptr<ASTName>(new ASTName(std::forward<Args>(args)...));     \
    }

#define AST_ALIAS(ASTName, alias)                                                      \
    template<typename... Args>                                                         \
    AST alias(Args&&... args) {                                                        \
        return ASTName::construct(std::forward<Args>(args)...);                        \
    }

    /*
    #define TEMPLATE_CONSTRUCTOR(constructor) \
    template<typename... Args>                                                         \
    friend AST constructor(Args&&... args);                                            \
    template<typename T>                                                               \
    friend AST constructor(std::initializer_list<T> args)

    #define REGISTER_AST(ClassName, constructor) \
    template<typename... Args>                                                         \
    inline expression constructor(Args&&... args) {                                    \
        return std::shared_ptr<ClassName>(new ClassName(std::forward<Args>(args)...)); \
    }                                                                                  \
    template<typename T>                                                               \
    inline expression constructor(std::initializer_list<T> args) {                     \
        return std::shared_ptr<ClassName>(                                             \
        new ClassName(std::forward<std::initializer_list<T>>(args)));              \
    }
     */
}  // namespace calcpp
