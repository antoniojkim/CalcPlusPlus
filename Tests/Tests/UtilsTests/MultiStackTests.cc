
#include <catch2/catch_all.hpp>

#include <calcpp/Utils/MultiStack.h>

using namespace calcpp;

namespace {

    TEST_CASE("MultiStack Tests", "[multistack][xpass]") {
        MultiStack<int> stack(10);
        stack.push(1);
        stack.pushStack();
        CHECK(stack.stackSize() == 0);
        stack.push(2);
        CHECK(stack.stackSize() == 1);
        CHECK(stack.size() == 2);

        int item = stack.pop();
        CHECK(item == 2);
        CHECK(stack.stackSize() == 0);
        stack.popStack();
        CHECK(stack.stackSize() == 1);

        stack.pushStack();
        stack.push(3);
        CHECK(stack.stackSize() == 1);
        stack.push(2, 1);
        CHECK(stack.stackSize() == 1);
        CHECK(stack.size() == 3);
    }

}  // namespace
