#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include <cassert>
#include <charconv>
#include <exception>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <tuple>
#include <vector>

#include "calcpp/Operators/Operators.h"
#include "calcpp/Parser/RecursiveDescent.h"
#include "calcpp/Scanner/Scanner.h"
#include "calcpp/Utils/Exception.h"

using namespace std;
using namespace calcpp;

/*
Purpose of this script is to test the calcpp language compiler. Can be compiled and run
using the `./run` bash script.
 */

int main() {
    const std::string input = "3*(2+4); 4 + 5 * 6; 7 + sin(3) / 15";
    auto tokens = calcpp::scan(input);

    std::unique_ptr<Parser> parser = std::make_unique<RecursiveDescent>();
    std::vector<AST> statements;
    try {
        statements = parser->parse(tokens);
        cout << "Parsed " << statements.size() << " statements" << endl;
        for (auto ast : statements) {
            cout << "    ";
            ast->repr(cout) << endl;
        }
    } catch (std::exception& e) {
        cout << e.what() << endl;
        throw;
    }

    std::unique_ptr<llvm::LLVMContext> context = std::make_unique<llvm::LLVMContext>();
    std::unique_ptr<llvm::Module> module =
        std::make_unique<llvm::Module>("calcpp jit", *context);
    std::unique_ptr<llvm::IRBuilder<>> builder =
        std::make_unique<llvm::IRBuilder<>>(*context);
}
