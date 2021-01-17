#include <iostream>
#include <vector>

#include "Exception.h"

namespace calcpp {

    template<typename T>
    class MultiStack {
        std::vector<T> stack;
        std::vector<size_t> splits;

      public:
        MultiStack(size_t capacity) {
            stack.reserve(capacity);
            splits.reserve(capacity);
        }

        size_t size() { return stack.size(); }
        size_t stackSize() {
            if (!splits.empty()) { return stack.size() - splits.back(); }
            return stack.size();
        }
        size_t numStack() { return splits.size() + 1; }

        bool empty() { return stack.empty(); }
        bool emptyStack() { return stackSize() == 0; }

        void push(T item, size_t level = 0) {
            if (level == 0) {
                stack.emplace_back(item);
                return;
            }
            if (level > splits.size()) {
                THROW_ERROR("Cannot push item on level " << level);
            }
            size_t split = splits[splits.size() - level];
            stack.insert(stack.begin() + split, item);
            for (size_t i = 1; i <= level; ++i) { ++splits[splits.size() - i]; }
        }
        T pop() {
            if (stackSize() == 0) { THROW_ERROR("Cannot pop off of empty stack"); }
            T item = std::move(stack.back());
            stack.pop_back();
            return std::move(item);
        }

        void pushStack() { splits.emplace_back(stack.size()); }
        void popStack(bool merge = true) {
            if (!merge && stackSize() > 0) {
                THROW_ERROR("Cannot pop an non-empty stack");
            }
            if (!splits.empty()) { splits.pop_back(); }
        }

        auto begin() { return stack.begin(); }
        auto end() { return stack.end(); }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const MultiStack<U>& stack);
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const MultiStack<T>& stack) {
        auto split = stack.splits.begin();
        out << "{";
        for (size_t i = 0; i < stack.stack.size(); ++i) {
            if (i == *split) {
                out << " |";
                ++split;
            }
            out << " " << stack.stack[i];
        }
        return out << " }";
    }

}  // namespace calcpp
