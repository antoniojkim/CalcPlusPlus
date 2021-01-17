#include <cassert>
#include <exception>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include <catch2/catch_all.hpp>

#include <calcpp/Scanner/Scanner.h>

using namespace calcpp;
using namespace std;

namespace {

    const vector<pair<string, vector<Token::Kind>>> success_tests = {
        {"1", {Token::Kind::NUM}},
        {"1298367", {Token::Kind::NUM}},
        {"1.24543", {Token::Kind::NUM}},
        {".5", {Token::Kind::NUM}},
        {"1.35e7", {Token::Kind::NUM}},
        {"1.36547e-14", {Token::Kind::NUM}},
        {"6.4i", {Token::Kind::COMPLEX}},
        {"5.33e2j", {Token::Kind::COMPLEX}},
        {"0x123a4b", {Token::Kind::HEX}},
        {"0b1101010101", {Token::Kind::BIN}},
        {"abc", {Token::Kind::ID}},
        {"g1", {Token::Kind::ID}},
        {"g_1", {Token::Kind::ID}},
        {"_g1", {Token::Kind::ID}},
        {"g1_", {Token::Kind::ID}},
        {"1_a", {Token::Kind::NUM, Token::Kind::ID}},
        {"+", {Token::Kind::PLUS}},
        {"+=", {Token::Kind::PLUS_EQUALS}},
        {"-", {Token::Kind::MINUS}},
        {"-=", {Token::Kind::MINUS_EQUALS}},
        {"1+2", {Token::Kind::NUM, Token::Kind::PLUS, Token::Kind::NUM}},
        {"/", {Token::Kind::SLASH}},
        {"//", {Token::Kind::SLASH_SLASH}},
        {"/=", {Token::Kind::SLASH_EQUALS}},
        {"*", {Token::Kind::STAR}},
        {"**", {Token::Kind::STAR_STAR}},
        {"|", {Token::Kind::PIPE}},
        {"||", {Token::Kind::PIPE_PIPE}},
        {"&", {Token::Kind::AMP}},
        {"&&", {Token::Kind::AMP_AMP}},
        {"=", {Token::Kind::EQUALS}},
        {"==", {Token::Kind::EQUALS_EQUALS}},
        {":", {Token::Kind::COLON}},
        {"::", {Token::Kind::COLON_COLON}},
        {":=", {Token::Kind::COLON_EQUALS}},
        {"<", {Token::Kind::LT}},
        {"<=", {Token::Kind::LT_EQUALS}},
        {"<<", {Token::Kind::LT_LT}},
        {"<<=", {Token::Kind::LT_LT_EQUALS}},
        {">", {Token::Kind::GT}},
        {">=", {Token::Kind::GT_EQUALS}},
        {">>", {Token::Kind::GT_GT}},
        {">>=", {Token::Kind::GT_GT_EQUALS}},
        {"->", {Token::Kind::R_ARROW}},
        {"<-", {Token::Kind::L_ARROW}},
        {"= =", {Token::Kind::EQUALS, Token::Kind::EQUALS}},
        {"!", {Token::Kind::EXCL}},
        {"!!", {Token::Kind::EXCL_EXCL}},
        {"!=", {Token::Kind::EXCL_EQUALS}},
        {"(", {Token::Kind::LPAREN}},
        {")", {Token::Kind::RPAREN}},
        {"(a)", {Token::Kind::LPAREN, Token::Kind::ID, Token::Kind::RPAREN}},
        {"[", {Token::Kind::LBRACE}},
        {"]", {Token::Kind::RBRACE}},
        {"[123]", {Token::Kind::LBRACE, Token::Kind::NUM, Token::Kind::RBRACE}},
        {"{", {Token::Kind::LCURLY}},
        {"}", {Token::Kind::RCURLY}},
        {"{1, a}",
         {Token::Kind::LCURLY,
          Token::Kind::NUM,
          Token::Kind::COMMA,
          Token::Kind::ID,
          Token::Kind::RCURLY}},
        {"#", {Token::Kind::HASH}},
        {"@", {Token::Kind::AT}},
        {"\\'", {Token::Kind::APOSTROPHE}},
        {"\\\"", {Token::Kind::QUOTE}},
        {"\"string\"", {Token::Kind::STRING}},
        {"'test whitespace'", {Token::Kind::STRING}},
        {"..", {Token::Kind::DOT_DOT}},
        {"...", {Token::Kind::ELLIPSES}},
        {"∞", {Token::Kind::INF}},
        {"λ", {Token::Kind::GREEK}},
        {"α φ", {Token::Kind::GREEK, Token::Kind::GREEK}}};

    TEST_CASE("Successful Scan Tests", "[scanner][xpass]") {
        for (const auto& test : success_tests) {
            const auto& input = test.first;
            INFO("Input: " << input);

            auto tokens = calcpp::scan(input);

            const auto& kinds = test.second;
            CHECK(tokens.size() == kinds.size());

            size_t i = 0;
            size_t num_mismatches = 0;
            for (const auto& token : tokens) {
                if (token.kind != kinds[i]) {
                    ++num_mismatches;
                    INFO(
                        "Mismatch on " << token.view() << ": " << token.kind
                                       << " != " << kinds[i]);
                }
                ++i;
            }
            CHECK(num_mismatches == 0);
        }
    }  // namespace

    const vector<string> fail_tests = {"1.2.3",
                                       "1.2e3.4",
                                       "1.2e--4",
                                       ".2.3",
                                       "0x + 2",
                                       "0xg",
                                       "0x1a.3",
                                       "0b01.10",
                                       "\"string",
                                       "\"string'"};

    TEST_CASE("Unsuccessful Scan Tests", "[scanner][xfail]") {
        for (const auto& input : fail_tests) {
            INFO("input: " << input);
            CHECK_THROWS(calcpp::scan(input));
        }
    }

    const vector<string> benchmark_inputs = {
        "(1 + 2, sin(3), 3 // 4 ** 5) >> sdfguh534523 + \"test string\" .457i "
        "0x2353abf34c 0b0101010001"};

    TEST_CASE("Benchmark Scanner", "[.][benchmark]") {
        BENCHMARK("Scanner Benchmark 1") { return calcpp::scan(benchmark_inputs[0]); };
    }

}  // namespace
