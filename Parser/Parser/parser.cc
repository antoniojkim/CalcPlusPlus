
#include "parser.h"
#include "../Scanner/scanner.h"
#include "StringUtils.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;


unordered_set<string> terminals({
	"AMP",
	"APOSTROPHE",
	"BACKSLASH",
	"BACKTICK",
	"BOF",
	"BOF_",
	"CARET",
	"CARET_PIPE",
	"COLON",
	"COLON_EQUALS",
	"COMMA",
	"DOLLAR",
	"DOT",
	"EOF",
	"EOF_",
	"EQUALS",
	"EXCL",
	"FALSE_",
	"GT_GT",
	"ID",
	"LBRACE",
	"LPAREN",
	"LSQUARE",
	"LT_LT",
	"L_ARROW",
	"MINUS",
	"NONE_",
	"NULL_",
	"NUM",
	"PCT",
	"PIPE",
	"PLUS",
	"POUND",
	"QUESTION",
	"QUOTE",
	"RBRACE",
	"RPAREN",
	"RSQUARE",
	"R_ARROW",
	"SEMICOLON",
	"SLASH",
	"SLASH_SLASH",
	"STAR",
	"STAR_STAR",
	"STR",
	"TILDE",
	"TRUE_",
	"UNDERSCORE"
});

unordered_set<string> nonterminals({
	"arglist",
	"expr",
	"expr1",
	"expr11",
	"expr12",
	"expr13",
	"expr3",
	"expr4",
	"expr5",
	"expr6",
	"expr7",
	"exprl",
	"exprn",
	"factor",
	"lvalue",
	"statement"
});

vector<list<string>> rules ({
	{"statement", "expr"},
	{"expr", "lvalue", "EQUALS", "expr1"},
	{"expr", "lvalue", "COLON_EQUALS", "expr1"},
	{"expr", "lvalue", "L_ARROW", "expr1"},
	{"expr", "expr1"},
	{"expr1", "expr3"},
	{"expr3", "TILDE", "expr3"},
	{"expr3", "expr4"},
	{"expr4", "expr4", "CARET", "expr5"},
	{"expr4", "expr4", "EXCL"},
	{"expr4", "expr5"},
	{"expr5", "expr5", "STAR", "expr6"},
	{"expr5", "expr5", "SLASH", "expr6"},
	{"expr5", "expr5", "SLASH_SLASH", "expr6"},
	{"expr5", "expr5", "PCT", "expr6"},
	{"expr5", "expr6"},
	{"expr6", "expr6", "PLUS", "expr7"},
	{"expr6", "expr6", "MINUS", "expr7"},
	{"expr6", "expr7"},
	{"expr7", "expr7", "LT_LT", "expr11"},
	{"expr7", "expr7", "GT_GT", "expr11"},
	{"expr7", "expr11"},
	{"expr11", "expr11", "AMP", "expr12"},
	{"expr11", "expr12"},
	{"expr12", "expr12", "CARET_PIPE", "expr13"},
	{"expr12", "expr13"},
	{"expr13", "expr13", "PIPE", "exprn"},
	{"expr13", "exprn"},
	{"exprn", "PIPE", "expr", "PIPE"},
	{"exprn", "LPAREN", "expr", "RPAREN"},
	{"exprn", "ID", "LPAREN", "RPAREN"},
	{"exprn", "ID", "LPAREN", "arglist", "RPAREN"},
	{"exprn", "exprl"},
	{"exprl", "factor"},
	{"exprl", "lvalue"},
	{"factor", "NUM"},
	{"factor", "NONE_"},
	{"factor", "TRUE_"},
	{"factor", "FALSE_"},
	{"factor", "ID"},
	{"lvalue", "ID"},
	{"lvalue", "LPAREN", "lvalue", "RPAREN"},
	{"arglist", "expr"},
	{"arglist", "expr", "COMMA", "arglist"},
	{"start", "BOF_", "statement", "EOF_"}
});

unordered_map<int, unordered_map<string, pair<bool, int>>> transitions({
	{0, {{"BOF_", {false, 1}}}},
	{1, {{"statement", {false, 2}}, {"expr", {false, 3}}, {"lvalue", {false, 4}}, {"expr1", {false, 5}}, {"ID", {false, 6}}, {"LPAREN", {false, 7}}, {"expr3", {false, 8}}, {"TILDE", {false, 9}}, {"expr4", {false, 10}}, {"expr5", {false, 11}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{2, {{"EOF_", {false, 25}}}},
	{3, {{"EOF_", {true, 0}}}},
	{4, {{"EQUALS", {false, 26}}, {"COLON_EQUALS", {false, 27}}, {"L_ARROW", {false, 28}}, {"AMP", {true, 34}}, {"CARET", {true, 34}}, {"CARET_PIPE", {true, 34}}, {"EXCL", {true, 34}}, {"GT_GT", {true, 34}}, {"LT_LT", {true, 34}}, {"MINUS", {true, 34}}, {"PCT", {true, 34}}, {"PIPE", {true, 34}}, {"PLUS", {true, 34}}, {"RPAREN", {true, 34}}, {"SLASH", {true, 34}}, {"SLASH_SLASH", {true, 34}}, {"STAR", {true, 34}}, {"COMMA", {true, 34}}, {"EOF_", {true, 34}}}},
	{5, {{"PIPE", {true, 4}}, {"RPAREN", {true, 4}}, {"COMMA", {true, 4}}, {"EOF_", {true, 4}}}},
	{6, {{"LPAREN", {false, 56}}, {"EQUALS", {true, 40}}, {"COLON_EQUALS", {true, 40}}, {"L_ARROW", {true, 40}}, {"AMP", {true, 39}}, {"CARET", {true, 39}}, {"CARET_PIPE", {true, 39}}, {"EXCL", {true, 39}}, {"GT_GT", {true, 39}}, {"LT_LT", {true, 39}}, {"MINUS", {true, 39}}, {"PCT", {true, 39}}, {"PIPE", {true, 39}}, {"PLUS", {true, 39}}, {"RPAREN", {true, 39}}, {"SLASH", {true, 39}}, {"SLASH_SLASH", {true, 39}}, {"STAR", {true, 39}}, {"COMMA", {true, 39}}, {"EOF_", {true, 39}}}},
	{7, {{"lvalue", {false, 63}}, {"expr", {false, 64}}, {"ID", {false, 6}}, {"expr1", {false, 5}}, {"expr3", {false, 8}}, {"TILDE", {false, 9}}, {"expr4", {false, 10}}, {"expr5", {false, 11}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{8, {{"PIPE", {true, 5}}, {"RPAREN", {true, 5}}, {"COMMA", {true, 5}}, {"EOF_", {true, 5}}}},
	{9, {{"expr3", {false, 33}}, {"expr4", {false, 10}}, {"expr5", {false, 11}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{10, {{"CARET", {false, 34}}, {"EXCL", {false, 35}}, {"PIPE", {true, 7}}, {"RPAREN", {true, 7}}, {"COMMA", {true, 7}}, {"EOF_", {true, 7}}}},
	{11, {{"STAR", {false, 37}}, {"SLASH", {false, 38}}, {"SLASH_SLASH", {false, 39}}, {"PCT", {false, 40}}, {"CARET", {true, 10}}, {"EXCL", {true, 10}}, {"PIPE", {true, 10}}, {"RPAREN", {true, 10}}, {"COMMA", {true, 10}}, {"EOF_", {true, 10}}}},
	{12, {{"PLUS", {false, 42}}, {"MINUS", {false, 43}}, {"CARET", {true, 15}}, {"EXCL", {true, 15}}, {"STAR", {true, 15}}, {"SLASH", {true, 15}}, {"SLASH_SLASH", {true, 15}}, {"PCT", {true, 15}}, {"PIPE", {true, 15}}, {"RPAREN", {true, 15}}, {"COMMA", {true, 15}}, {"EOF_", {true, 15}}}},
	{13, {{"LT_LT", {false, 45}}, {"GT_GT", {false, 46}}, {"CARET", {true, 18}}, {"EXCL", {true, 18}}, {"STAR", {true, 18}}, {"SLASH", {true, 18}}, {"SLASH_SLASH", {true, 18}}, {"PCT", {true, 18}}, {"PLUS", {true, 18}}, {"MINUS", {true, 18}}, {"PIPE", {true, 18}}, {"RPAREN", {true, 18}}, {"COMMA", {true, 18}}, {"EOF_", {true, 18}}}},
	{14, {{"AMP", {false, 48}}, {"CARET", {true, 21}}, {"EXCL", {true, 21}}, {"PCT", {true, 21}}, {"PLUS", {true, 21}}, {"SLASH", {true, 21}}, {"SLASH_SLASH", {true, 21}}, {"STAR", {true, 21}}, {"MINUS", {true, 21}}, {"LT_LT", {true, 21}}, {"GT_GT", {true, 21}}, {"PIPE", {true, 21}}, {"RPAREN", {true, 21}}, {"COMMA", {true, 21}}, {"EOF_", {true, 21}}}},
	{15, {{"CARET_PIPE", {false, 50}}, {"CARET", {true, 23}}, {"EXCL", {true, 23}}, {"LT_LT", {true, 23}}, {"MINUS", {true, 23}}, {"PCT", {true, 23}}, {"PLUS", {true, 23}}, {"SLASH", {true, 23}}, {"SLASH_SLASH", {true, 23}}, {"STAR", {true, 23}}, {"GT_GT", {true, 23}}, {"AMP", {true, 23}}, {"PIPE", {true, 23}}, {"RPAREN", {true, 23}}, {"COMMA", {true, 23}}, {"EOF_", {true, 23}}}},
	{16, {{"PIPE", {true, 25}}, {"AMP", {true, 25}}, {"CARET", {true, 25}}, {"EXCL", {true, 25}}, {"GT_GT", {true, 25}}, {"LT_LT", {true, 25}}, {"MINUS", {true, 25}}, {"PCT", {true, 25}}, {"PLUS", {true, 25}}, {"SLASH", {true, 25}}, {"SLASH_SLASH", {true, 25}}, {"STAR", {true, 25}}, {"CARET_PIPE", {true, 25}}, {"RPAREN", {true, 25}}, {"COMMA", {true, 25}}, {"EOF_", {true, 25}}}},
	{17, {{"AMP", {true, 27}}, {"CARET", {true, 27}}, {"CARET_PIPE", {true, 27}}, {"EXCL", {true, 27}}, {"GT_GT", {true, 27}}, {"LT_LT", {true, 27}}, {"MINUS", {true, 27}}, {"PCT", {true, 27}}, {"PLUS", {true, 27}}, {"SLASH", {true, 27}}, {"SLASH_SLASH", {true, 27}}, {"STAR", {true, 27}}, {"PIPE", {true, 27}}, {"RPAREN", {true, 27}}, {"COMMA", {true, 27}}, {"EOF_", {true, 27}}}},
	{18, {{"expr", {false, 54}}, {"lvalue", {false, 4}}, {"expr1", {false, 5}}, {"ID", {false, 6}}, {"LPAREN", {false, 7}}, {"expr3", {false, 8}}, {"TILDE", {false, 9}}, {"expr4", {false, 10}}, {"expr5", {false, 11}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{19, {{"AMP", {true, 32}}, {"CARET", {true, 32}}, {"CARET_PIPE", {true, 32}}, {"EXCL", {true, 32}}, {"GT_GT", {true, 32}}, {"LT_LT", {true, 32}}, {"MINUS", {true, 32}}, {"PCT", {true, 32}}, {"PIPE", {true, 32}}, {"PLUS", {true, 32}}, {"SLASH", {true, 32}}, {"SLASH_SLASH", {true, 32}}, {"STAR", {true, 32}}, {"RPAREN", {true, 32}}, {"COMMA", {true, 32}}, {"EOF_", {true, 32}}}},
	{20, {{"AMP", {true, 33}}, {"CARET", {true, 33}}, {"CARET_PIPE", {true, 33}}, {"EXCL", {true, 33}}, {"GT_GT", {true, 33}}, {"LT_LT", {true, 33}}, {"MINUS", {true, 33}}, {"PCT", {true, 33}}, {"PIPE", {true, 33}}, {"PLUS", {true, 33}}, {"RPAREN", {true, 33}}, {"SLASH", {true, 33}}, {"SLASH_SLASH", {true, 33}}, {"STAR", {true, 33}}, {"COMMA", {true, 33}}, {"EOF_", {true, 33}}}},
	{21, {{"AMP", {true, 35}}, {"CARET", {true, 35}}, {"CARET_PIPE", {true, 35}}, {"EXCL", {true, 35}}, {"GT_GT", {true, 35}}, {"LT_LT", {true, 35}}, {"MINUS", {true, 35}}, {"PCT", {true, 35}}, {"PIPE", {true, 35}}, {"PLUS", {true, 35}}, {"RPAREN", {true, 35}}, {"SLASH", {true, 35}}, {"SLASH_SLASH", {true, 35}}, {"STAR", {true, 35}}, {"COMMA", {true, 35}}, {"EOF_", {true, 35}}}},
	{22, {{"AMP", {true, 36}}, {"CARET", {true, 36}}, {"CARET_PIPE", {true, 36}}, {"EXCL", {true, 36}}, {"GT_GT", {true, 36}}, {"LT_LT", {true, 36}}, {"MINUS", {true, 36}}, {"PCT", {true, 36}}, {"PIPE", {true, 36}}, {"PLUS", {true, 36}}, {"RPAREN", {true, 36}}, {"SLASH", {true, 36}}, {"SLASH_SLASH", {true, 36}}, {"STAR", {true, 36}}, {"COMMA", {true, 36}}, {"EOF_", {true, 36}}}},
	{23, {{"AMP", {true, 37}}, {"CARET", {true, 37}}, {"CARET_PIPE", {true, 37}}, {"EXCL", {true, 37}}, {"GT_GT", {true, 37}}, {"LT_LT", {true, 37}}, {"MINUS", {true, 37}}, {"PCT", {true, 37}}, {"PIPE", {true, 37}}, {"PLUS", {true, 37}}, {"RPAREN", {true, 37}}, {"SLASH", {true, 37}}, {"SLASH_SLASH", {true, 37}}, {"STAR", {true, 37}}, {"COMMA", {true, 37}}, {"EOF_", {true, 37}}}},
	{24, {{"AMP", {true, 38}}, {"CARET", {true, 38}}, {"CARET_PIPE", {true, 38}}, {"EXCL", {true, 38}}, {"GT_GT", {true, 38}}, {"LT_LT", {true, 38}}, {"MINUS", {true, 38}}, {"PCT", {true, 38}}, {"PIPE", {true, 38}}, {"PLUS", {true, 38}}, {"RPAREN", {true, 38}}, {"SLASH", {true, 38}}, {"SLASH_SLASH", {true, 38}}, {"STAR", {true, 38}}, {"COMMA", {true, 38}}, {"EOF_", {true, 38}}}},
	{26, {{"expr1", {false, 29}}, {"expr3", {false, 8}}, {"TILDE", {false, 9}}, {"expr4", {false, 10}}, {"expr5", {false, 11}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{27, {{"expr1", {false, 66}}, {"expr3", {false, 8}}, {"TILDE", {false, 9}}, {"expr4", {false, 10}}, {"expr5", {false, 11}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{28, {{"expr1", {false, 73}}, {"expr3", {false, 8}}, {"TILDE", {false, 9}}, {"expr4", {false, 10}}, {"expr5", {false, 11}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{29, {{"PIPE", {true, 1}}, {"RPAREN", {true, 1}}, {"COMMA", {true, 1}}, {"EOF_", {true, 1}}}},
	{30, {{"expr", {false, 64}}, {"lvalue", {false, 63}}, {"expr1", {false, 5}}, {"ID", {false, 6}}, {"expr3", {false, 8}}, {"TILDE", {false, 9}}, {"expr4", {false, 10}}, {"expr5", {false, 11}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{31, {{"LPAREN", {false, 56}}, {"AMP", {true, 40}}, {"CARET", {true, 40}}, {"CARET_PIPE", {true, 40}}, {"EXCL", {true, 40}}, {"GT_GT", {true, 40}}, {"LT_LT", {true, 40}}, {"MINUS", {true, 40}}, {"PCT", {true, 40}}, {"PIPE", {true, 40}}, {"PLUS", {true, 40}}, {"RPAREN", {true, 40}}, {"SLASH", {true, 40}}, {"SLASH_SLASH", {true, 40}}, {"STAR", {true, 40}}, {"COMMA", {true, 40}}, {"EOF_", {true, 40}}, {"EQUALS", {true, 40}}, {"COLON_EQUALS", {true, 40}}, {"L_ARROW", {true, 40}}}},
	{32, {{"AMP", {true, 34}}, {"CARET", {true, 34}}, {"CARET_PIPE", {true, 34}}, {"EXCL", {true, 34}}, {"GT_GT", {true, 34}}, {"LT_LT", {true, 34}}, {"MINUS", {true, 34}}, {"PCT", {true, 34}}, {"PIPE", {true, 34}}, {"PLUS", {true, 34}}, {"RPAREN", {true, 34}}, {"SLASH", {true, 34}}, {"SLASH_SLASH", {true, 34}}, {"STAR", {true, 34}}, {"COMMA", {true, 34}}, {"EOF_", {true, 34}}}},
	{33, {{"PIPE", {true, 6}}, {"RPAREN", {true, 6}}, {"COMMA", {true, 6}}, {"EOF_", {true, 6}}}},
	{34, {{"expr5", {false, 36}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{35, {{"CARET", {true, 9}}, {"EXCL", {true, 9}}, {"PIPE", {true, 9}}, {"RPAREN", {true, 9}}, {"COMMA", {true, 9}}, {"EOF_", {true, 9}}}},
	{36, {{"STAR", {false, 37}}, {"SLASH", {false, 38}}, {"SLASH_SLASH", {false, 39}}, {"PCT", {false, 40}}, {"CARET", {true, 8}}, {"EXCL", {true, 8}}, {"PIPE", {true, 8}}, {"RPAREN", {true, 8}}, {"COMMA", {true, 8}}, {"EOF_", {true, 8}}}},
	{37, {{"expr6", {false, 41}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{38, {{"expr6", {false, 67}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{39, {{"expr6", {false, 71}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{40, {{"expr6", {false, 72}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{41, {{"PLUS", {false, 42}}, {"MINUS", {false, 43}}, {"CARET", {true, 11}}, {"EXCL", {true, 11}}, {"STAR", {true, 11}}, {"SLASH", {true, 11}}, {"SLASH_SLASH", {true, 11}}, {"PCT", {true, 11}}, {"PIPE", {true, 11}}, {"RPAREN", {true, 11}}, {"COMMA", {true, 11}}, {"EOF_", {true, 11}}}},
	{42, {{"expr7", {false, 44}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{43, {{"expr7", {false, 68}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{44, {{"LT_LT", {false, 45}}, {"GT_GT", {false, 46}}, {"CARET", {true, 16}}, {"EXCL", {true, 16}}, {"STAR", {true, 16}}, {"SLASH", {true, 16}}, {"SLASH_SLASH", {true, 16}}, {"PCT", {true, 16}}, {"PLUS", {true, 16}}, {"MINUS", {true, 16}}, {"PIPE", {true, 16}}, {"RPAREN", {true, 16}}, {"COMMA", {true, 16}}, {"EOF_", {true, 16}}}},
	{45, {{"expr11", {false, 47}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{46, {{"expr11", {false, 69}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{47, {{"AMP", {false, 48}}, {"CARET", {true, 19}}, {"EXCL", {true, 19}}, {"PCT", {true, 19}}, {"PLUS", {true, 19}}, {"SLASH", {true, 19}}, {"SLASH_SLASH", {true, 19}}, {"STAR", {true, 19}}, {"MINUS", {true, 19}}, {"LT_LT", {true, 19}}, {"GT_GT", {true, 19}}, {"PIPE", {true, 19}}, {"RPAREN", {true, 19}}, {"COMMA", {true, 19}}, {"EOF_", {true, 19}}}},
	{48, {{"expr12", {false, 49}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{49, {{"CARET_PIPE", {false, 50}}, {"CARET", {true, 22}}, {"EXCL", {true, 22}}, {"LT_LT", {true, 22}}, {"MINUS", {true, 22}}, {"PCT", {true, 22}}, {"PLUS", {true, 22}}, {"SLASH", {true, 22}}, {"SLASH_SLASH", {true, 22}}, {"STAR", {true, 22}}, {"GT_GT", {true, 22}}, {"AMP", {true, 22}}, {"PIPE", {true, 22}}, {"RPAREN", {true, 22}}, {"COMMA", {true, 22}}, {"EOF_", {true, 22}}}},
	{50, {{"expr13", {false, 51}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{51, {{"PIPE", {true, 24}}, {"AMP", {true, 24}}, {"CARET", {true, 24}}, {"EXCL", {true, 24}}, {"GT_GT", {true, 24}}, {"LT_LT", {true, 24}}, {"MINUS", {true, 24}}, {"PCT", {true, 24}}, {"PLUS", {true, 24}}, {"SLASH", {true, 24}}, {"SLASH_SLASH", {true, 24}}, {"STAR", {true, 24}}, {"CARET_PIPE", {true, 24}}, {"RPAREN", {true, 24}}, {"COMMA", {true, 24}}, {"EOF_", {true, 24}}}},
	{52, {{"exprn", {false, 53}}, {"PIPE", {false, 18}}, {"LPAREN", {false, 30}}, {"ID", {false, 31}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"lvalue", {false, 32}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{53, {{"AMP", {true, 26}}, {"CARET", {true, 26}}, {"CARET_PIPE", {true, 26}}, {"EXCL", {true, 26}}, {"GT_GT", {true, 26}}, {"LT_LT", {true, 26}}, {"MINUS", {true, 26}}, {"PCT", {true, 26}}, {"PLUS", {true, 26}}, {"SLASH", {true, 26}}, {"SLASH_SLASH", {true, 26}}, {"STAR", {true, 26}}, {"PIPE", {true, 26}}, {"RPAREN", {true, 26}}, {"COMMA", {true, 26}}, {"EOF_", {true, 26}}}},
	{54, {{"PIPE", {false, 55}}}},
	{55, {{"AMP", {true, 28}}, {"CARET", {true, 28}}, {"CARET_PIPE", {true, 28}}, {"EXCL", {true, 28}}, {"GT_GT", {true, 28}}, {"LT_LT", {true, 28}}, {"MINUS", {true, 28}}, {"PCT", {true, 28}}, {"PIPE", {true, 28}}, {"PLUS", {true, 28}}, {"SLASH", {true, 28}}, {"SLASH_SLASH", {true, 28}}, {"STAR", {true, 28}}, {"RPAREN", {true, 28}}, {"COMMA", {true, 28}}, {"EOF_", {true, 28}}}},
	{56, {{"RPAREN", {false, 57}}, {"arglist", {false, 58}}, {"expr", {false, 59}}, {"lvalue", {false, 4}}, {"expr1", {false, 5}}, {"ID", {false, 6}}, {"LPAREN", {false, 7}}, {"expr3", {false, 8}}, {"TILDE", {false, 9}}, {"expr4", {false, 10}}, {"expr5", {false, 11}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{57, {{"AMP", {true, 30}}, {"CARET", {true, 30}}, {"CARET_PIPE", {true, 30}}, {"EXCL", {true, 30}}, {"GT_GT", {true, 30}}, {"LT_LT", {true, 30}}, {"MINUS", {true, 30}}, {"PCT", {true, 30}}, {"PIPE", {true, 30}}, {"PLUS", {true, 30}}, {"SLASH", {true, 30}}, {"SLASH_SLASH", {true, 30}}, {"STAR", {true, 30}}, {"RPAREN", {true, 30}}, {"COMMA", {true, 30}}, {"EOF_", {true, 30}}}},
	{58, {{"RPAREN", {false, 60}}}},
	{59, {{"COMMA", {false, 61}}, {"RPAREN", {true, 42}}}},
	{60, {{"AMP", {true, 31}}, {"CARET", {true, 31}}, {"CARET_PIPE", {true, 31}}, {"EXCL", {true, 31}}, {"GT_GT", {true, 31}}, {"LT_LT", {true, 31}}, {"MINUS", {true, 31}}, {"PCT", {true, 31}}, {"PIPE", {true, 31}}, {"PLUS", {true, 31}}, {"SLASH", {true, 31}}, {"SLASH_SLASH", {true, 31}}, {"STAR", {true, 31}}, {"RPAREN", {true, 31}}, {"COMMA", {true, 31}}, {"EOF_", {true, 31}}}},
	{61, {{"arglist", {false, 62}}, {"expr", {false, 59}}, {"lvalue", {false, 4}}, {"expr1", {false, 5}}, {"ID", {false, 6}}, {"LPAREN", {false, 7}}, {"expr3", {false, 8}}, {"TILDE", {false, 9}}, {"expr4", {false, 10}}, {"expr5", {false, 11}}, {"expr6", {false, 12}}, {"expr7", {false, 13}}, {"expr11", {false, 14}}, {"expr12", {false, 15}}, {"expr13", {false, 16}}, {"exprn", {false, 17}}, {"PIPE", {false, 18}}, {"exprl", {false, 19}}, {"factor", {false, 20}}, {"NUM", {false, 21}}, {"NONE_", {false, 22}}, {"TRUE_", {false, 23}}, {"FALSE_", {false, 24}}}},
	{62, {{"RPAREN", {true, 43}}}},
	{63, {{"RPAREN", {true, 34}}, {"EQUALS", {false, 26}}, {"COLON_EQUALS", {false, 27}}, {"L_ARROW", {false, 28}}, {"AMP", {true, 34}}, {"CARET", {true, 34}}, {"CARET_PIPE", {true, 34}}, {"EXCL", {true, 34}}, {"GT_GT", {true, 34}}, {"LT_LT", {true, 34}}, {"MINUS", {true, 34}}, {"PCT", {true, 34}}, {"PIPE", {true, 34}}, {"PLUS", {true, 34}}, {"SLASH", {true, 34}}, {"SLASH_SLASH", {true, 34}}, {"STAR", {true, 34}}, {"COMMA", {true, 34}}, {"EOF_", {true, 34}}}},
	{64, {{"RPAREN", {false, 70}}}},
	{65, {{"EQUALS", {true, 41}}, {"COLON_EQUALS", {true, 41}}, {"L_ARROW", {true, 41}}, {"AMP", {true, 41}}, {"CARET", {true, 41}}, {"CARET_PIPE", {true, 41}}, {"EXCL", {true, 41}}, {"GT_GT", {true, 41}}, {"LT_LT", {true, 41}}, {"MINUS", {true, 41}}, {"PCT", {true, 41}}, {"PIPE", {true, 41}}, {"PLUS", {true, 41}}, {"RPAREN", {true, 41}}, {"SLASH", {true, 41}}, {"SLASH_SLASH", {true, 41}}, {"STAR", {true, 41}}, {"COMMA", {true, 41}}, {"EOF_", {true, 41}}}},
	{66, {{"PIPE", {true, 2}}, {"RPAREN", {true, 2}}, {"COMMA", {true, 2}}, {"EOF_", {true, 2}}}},
	{67, {{"PLUS", {false, 42}}, {"MINUS", {false, 43}}, {"CARET", {true, 12}}, {"EXCL", {true, 12}}, {"STAR", {true, 12}}, {"SLASH", {true, 12}}, {"SLASH_SLASH", {true, 12}}, {"PCT", {true, 12}}, {"PIPE", {true, 12}}, {"RPAREN", {true, 12}}, {"COMMA", {true, 12}}, {"EOF_", {true, 12}}}},
	{68, {{"LT_LT", {false, 45}}, {"GT_GT", {false, 46}}, {"CARET", {true, 17}}, {"EXCL", {true, 17}}, {"STAR", {true, 17}}, {"SLASH", {true, 17}}, {"SLASH_SLASH", {true, 17}}, {"PCT", {true, 17}}, {"PLUS", {true, 17}}, {"MINUS", {true, 17}}, {"PIPE", {true, 17}}, {"RPAREN", {true, 17}}, {"COMMA", {true, 17}}, {"EOF_", {true, 17}}}},
	{69, {{"AMP", {false, 48}}, {"CARET", {true, 20}}, {"EXCL", {true, 20}}, {"PCT", {true, 20}}, {"PLUS", {true, 20}}, {"SLASH", {true, 20}}, {"SLASH_SLASH", {true, 20}}, {"STAR", {true, 20}}, {"MINUS", {true, 20}}, {"LT_LT", {true, 20}}, {"GT_GT", {true, 20}}, {"PIPE", {true, 20}}, {"RPAREN", {true, 20}}, {"COMMA", {true, 20}}, {"EOF_", {true, 20}}}},
	{70, {{"AMP", {true, 29}}, {"CARET", {true, 29}}, {"CARET_PIPE", {true, 29}}, {"EXCL", {true, 29}}, {"GT_GT", {true, 29}}, {"LT_LT", {true, 29}}, {"MINUS", {true, 29}}, {"PCT", {true, 29}}, {"PIPE", {true, 29}}, {"PLUS", {true, 29}}, {"SLASH", {true, 29}}, {"SLASH_SLASH", {true, 29}}, {"STAR", {true, 29}}, {"RPAREN", {true, 29}}, {"COMMA", {true, 29}}, {"EOF_", {true, 29}}}},
	{71, {{"PLUS", {false, 42}}, {"MINUS", {false, 43}}, {"CARET", {true, 13}}, {"EXCL", {true, 13}}, {"STAR", {true, 13}}, {"SLASH", {true, 13}}, {"SLASH_SLASH", {true, 13}}, {"PCT", {true, 13}}, {"PIPE", {true, 13}}, {"RPAREN", {true, 13}}, {"COMMA", {true, 13}}, {"EOF_", {true, 13}}}},
	{72, {{"PLUS", {false, 42}}, {"MINUS", {false, 43}}, {"CARET", {true, 14}}, {"EXCL", {true, 14}}, {"STAR", {true, 14}}, {"SLASH", {true, 14}}, {"SLASH_SLASH", {true, 14}}, {"PCT", {true, 14}}, {"PIPE", {true, 14}}, {"RPAREN", {true, 14}}, {"COMMA", {true, 14}}, {"EOF_", {true, 14}}}},
	{73, {{"PIPE", {true, 3}}, {"RPAREN", {true, 3}}, {"COMMA", {true, 3}}, {"EOF_", {true, 3}}}}
});


template <class T>
T getNext(const string& str) {
    istringstream iss{str};
    T i;
    if (!(iss >> i)) throw "Failed to get next from string";
    return i;
}

template <class T>
T getNext(istringstream& iss) {
    T i;
    if (!(iss >> i)) throw "Failed to get next from istringstream";
    return i;
}

Parser::Parser() {}

unique_ptr<ParseTree> Parser::parse(const string& input,
                                         const bool& showTokens) {
    list<Token> tokens;
    tokens.emplace_back(Token{"BOF_", Type::BOF_});
    scan(input, tokens);
    tokens.emplace_back(Token{"EOF_", Type::EOF_});
    if (showTokens) {
        print(cout, tokens, "\n", true) << endl << endl;
    }
    return parse(tokens);
}

unique_ptr<ParseTree> Parser::parse(list<Token>& tokens) {
    // int currentState = 0;
    list<unique_ptr<ParseTree>> symbolStack;
    list<int> stateStack;
    stateStack.emplace_back(0);

    for (auto& token : tokens) {
        string typeString = getTypeString(token.type);
        while (transitions[stateStack.back()].count(typeString) > 0 &&
               transitions[stateStack.back()][typeString].first == true) {
            int rule = transitions[stateStack.back()][typeString].second;

            NonTerminal* nt = new NonTerminal(rules[rule]);
            nt->reserve(rules[rule].size() - 1);

            for (size_t j = 1; j < rules[rule].size(); ++j) {
                nt->addChild(symbolStack.back());
                symbolStack.pop_back();
                stateStack.pop_back();
            }
            reverse(nt->getChildren().begin(), nt->getChildren().end());
            unique_ptr<ParseTree> tree{nt};
            symbolStack.emplace_back(move(tree));
            stateStack.emplace_back(
                transitions[stateStack.back()][rules[rule].front()].second);
        }

        symbolStack.emplace_back(make_unique<Terminal>(token));

        if (transitions[stateStack.back()].count(
                symbolStack.back()->getRoot()) == 0) {
            ostringstream oss;
            oss << "ERROR at \"" << token.lexeme << "\"" << endl
                << "State Stack: " << endl;
            for (auto& state : stateStack) {
                oss << "    " << state << endl;
            }
            throw oss.str();
        }

        stateStack.emplace_back(
            transitions[stateStack.back()][symbolStack.back()->getRoot()]
                .second);
    }

    // cout << symbolStack.size() << endl;
    // for (auto& s : symbolStack){
    //     cout << s->getRoot() << endl;
    // }
    symbolStack.pop_back();

    unique_ptr<ParseTree> tree = move(symbolStack.back());

    return tree;
}

string actions[2] = {"SHIFT", "REDUCE"};
ostream& operator<<(ostream& out, Parser& parser) {
    out << "Terminals:" << endl;
    for (auto& terminal : terminals) {
        out << "    " << terminal << endl;
    }
    out << "Non Terminals:" << endl;
    for (auto& nonterminal : nonterminals) {
        out << "    " << nonterminal << endl;
    }
    out << "Rules:" << endl;
    for (auto& rule : rules) {
        out << "    " << join(rule, ' ') << endl;
    }
    out << "Transitions:" << endl;
    for (auto& state : transitions) {
        for (auto& symbol : state.second) {
            out << "    " << state.first << " " << symbol.first << " "
                << actions[symbol.second.first] << " " << symbol.second.second
                << endl;
        }
    }
    return out;
}