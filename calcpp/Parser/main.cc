#include <cassert>
#include <charconv>
#include <exception>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "../Expressions/ExpressionTypes/Types.h"
#include "../Scanner/Scanner.h"
#include "../Utils/MultiStack.h"

using namespace std;
using namespace calcpp;

int main() {
    const std::string input = "3*(2+4)";
    auto tokens = calcpp::scan(input);
}
