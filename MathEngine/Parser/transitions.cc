
#include "transitions.h"

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
	"HEX",
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
	"UNDERSCORE",
	"X",
	"Y"
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
	"exprn",
	"factor",
	"lvalue",
	"multiid",
	"statement"
});

vector<list<string>> rules ({
	{"statement", "expr"},
	{"expr", "lvalue", "EQUALS", "expr1"},
	{"expr", "lvalue", "COLON_EQUALS", "expr1"},
	{"expr", "lvalue", "L_ARROW", "expr1"},
	{"expr", "expr1"},
	{"expr1", "expr13"},
	{"expr13", "expr13", "PIPE", "expr12"},
	{"expr13", "expr12"},
	{"expr12", "expr12", "CARET_PIPE", "expr11"},
	{"expr12", "expr11"},
	{"expr11", "expr11", "AMP", "expr7"},
	{"expr11", "expr7"},
	{"expr7", "expr7", "LT_LT", "expr6"},
	{"expr7", "expr7", "GT_GT", "expr6"},
	{"expr7", "expr6"},
	{"expr6", "expr6", "PLUS", "expr5"},
	{"expr6", "expr6", "MINUS", "expr5"},
	{"expr6", "expr5"},
	{"expr5", "expr5", "STAR", "expr4"},
	{"expr5", "expr5", "SLASH", "expr4"},
	{"expr5", "expr5", "SLASH_SLASH", "expr4"},
	{"expr5", "expr5", "PCT", "expr4"},
	{"expr5", "exprn", "exprn"},
	{"expr5", "expr4"},
	{"expr4", "expr4", "CARET", "expr3"},
	{"expr4", "expr4", "EXCL"},
	{"expr4", "expr3"},
	{"expr3", "TILDE", "exprn"},
	{"expr3", "exprn"},
	{"exprn", "PIPE", "expr", "PIPE"},
	{"exprn", "LPAREN", "expr", "RPAREN"},
	{"exprn", "multiid", "LPAREN", "RPAREN"},
	{"exprn", "multiid", "LPAREN", "arglist", "RPAREN"},
	{"exprn", "multiid", "factor"},
	{"exprn", "lvalue"},
	{"multiid", "multiid", "ID"},
	{"multiid"},
	{"factor", "NUM"},
	{"factor", "X"},
	{"factor", "Y"},
	{"factor", "NONE_"},
	{"factor", "TRUE_"},
	{"factor", "FALSE_"},
	{"lvalue", "LPAREN", "lvalue", "RPAREN"},
	{"arglist", "expr"},
	{"arglist", "expr", "COMMA", "arglist"},
	{"start", "BOF_", "statement", "EOF_"}
});

unordered_map<int, unordered_map<string, pair<bool, int>>> transitions({
	{0, {{"BOF_", {false, 1}}}},
	{1, {{"statement", {false, 2}}, {"expr", {false, 3}}, {"lvalue", {false, 4}}, {"expr1", {false, 5}}, {"LPAREN", {true, 36}}, {"expr13", {false, 7}}, {"expr12", {false, 8}}, {"expr11", {false, 9}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"multiid", {false, 16}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{2, {{"EOF_", {false, 19}}}},
	{3, {{"EOF_", {true, 0}}}},
	{4, {{"EQUALS", {false, 20}}, {"COLON_EQUALS", {false, 21}}, {"L_ARROW", {false, 22}}, {"FALSE_", {true, 34}}, {"ID", {true, 34}}, {"LPAREN", {true, 34}}, {"NONE_", {true, 34}}, {"NUM", {true, 34}}, {"PIPE", {true, 34}}, {"TRUE_", {true, 34}}, {"X", {true, 34}}, {"Y", {true, 34}}, {"AMP", {true, 34}}, {"CARET_PIPE", {true, 34}}, {"GT_GT", {true, 34}}, {"LT_LT", {true, 34}}, {"MINUS", {true, 34}}, {"PCT", {true, 34}}, {"PLUS", {true, 34}}, {"SLASH", {true, 34}}, {"SLASH_SLASH", {true, 34}}, {"STAR", {true, 34}}, {"CARET", {true, 34}}, {"EXCL", {true, 34}}, {"RPAREN", {true, 34}}, {"COMMA", {true, 34}}, {"EOF_", {true, 34}}}},
	{5, {{"PIPE", {true, 4}}, {"RPAREN", {true, 4}}, {"COMMA", {true, 4}}, {"EOF_", {true, 4}}}},
	{6, {{"lvalue", {false, 50}}, {"expr", {false, 51}}, {"expr1", {false, 5}}, {"expr13", {false, 7}}, {"expr12", {false, 8}}, {"expr11", {false, 9}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"multiid", {false, 16}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"LPAREN", {true, 36}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{7, {{"PIPE", {true, 5}}, {"RPAREN", {true, 5}}, {"COMMA", {true, 5}}, {"EOF_", {true, 5}}}},
	{8, {{"CARET_PIPE", {false, 28}}, {"PIPE", {true, 7}}, {"RPAREN", {true, 7}}, {"COMMA", {true, 7}}, {"EOF_", {true, 7}}}},
	{9, {{"AMP", {false, 30}}, {"PIPE", {true, 9}}, {"CARET_PIPE", {true, 9}}, {"RPAREN", {true, 9}}, {"COMMA", {true, 9}}, {"EOF_", {true, 9}}}},
	{10, {{"LT_LT", {false, 32}}, {"GT_GT", {false, 33}}, {"CARET_PIPE", {true, 11}}, {"PIPE", {true, 11}}, {"AMP", {true, 11}}, {"RPAREN", {true, 11}}, {"COMMA", {true, 11}}, {"EOF_", {true, 11}}}},
	{11, {{"PLUS", {false, 35}}, {"MINUS", {false, 36}}, {"AMP", {true, 14}}, {"CARET_PIPE", {true, 14}}, {"PIPE", {true, 14}}, {"LT_LT", {true, 14}}, {"GT_GT", {true, 14}}, {"RPAREN", {true, 14}}, {"COMMA", {true, 14}}, {"EOF_", {true, 14}}}},
	{12, {{"STAR", {false, 38}}, {"SLASH", {false, 39}}, {"SLASH_SLASH", {false, 40}}, {"PCT", {false, 41}}, {"AMP", {true, 17}}, {"CARET_PIPE", {true, 17}}, {"LT_LT", {true, 17}}, {"PIPE", {true, 17}}, {"GT_GT", {true, 17}}, {"PLUS", {true, 17}}, {"MINUS", {true, 17}}, {"RPAREN", {true, 17}}, {"COMMA", {true, 17}}, {"EOF_", {true, 17}}}},
	{13, {{"exprn", {false, 75}}, {"PIPE", {true, 28}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"AMP", {true, 28}}, {"CARET", {true, 28}}, {"CARET_PIPE", {true, 28}}, {"GT_GT", {true, 28}}, {"LT_LT", {true, 28}}, {"MINUS", {true, 28}}, {"PCT", {true, 28}}, {"PLUS", {true, 28}}, {"SLASH", {true, 28}}, {"SLASH_SLASH", {true, 28}}, {"STAR", {true, 28}}, {"EXCL", {true, 28}}, {"RPAREN", {true, 28}}, {"COMMA", {true, 28}}, {"EOF_", {true, 28}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{14, {{"CARET", {false, 44}}, {"EXCL", {false, 45}}, {"AMP", {true, 23}}, {"CARET_PIPE", {true, 23}}, {"GT_GT", {true, 23}}, {"LT_LT", {true, 23}}, {"PIPE", {true, 23}}, {"PLUS", {true, 23}}, {"MINUS", {true, 23}}, {"STAR", {true, 23}}, {"SLASH", {true, 23}}, {"SLASH_SLASH", {true, 23}}, {"PCT", {true, 23}}, {"RPAREN", {true, 23}}, {"COMMA", {true, 23}}, {"EOF_", {true, 23}}}},
	{15, {{"expr", {false, 48}}, {"lvalue", {false, 4}}, {"expr1", {false, 5}}, {"LPAREN", {true, 36}}, {"expr13", {false, 7}}, {"expr12", {false, 8}}, {"expr11", {false, 9}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"multiid", {false, 16}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{16, {{"LPAREN", {false, 59}}, {"factor", {false, 60}}, {"ID", {false, 61}}, {"NUM", {false, 62}}, {"X", {false, 63}}, {"Y", {false, 64}}, {"NONE_", {false, 65}}, {"TRUE_", {false, 66}}, {"FALSE_", {false, 67}}}},
	{17, {{"AMP", {true, 26}}, {"CARET_PIPE", {true, 26}}, {"GT_GT", {true, 26}}, {"LT_LT", {true, 26}}, {"MINUS", {true, 26}}, {"PIPE", {true, 26}}, {"PLUS", {true, 26}}, {"STAR", {true, 26}}, {"SLASH", {true, 26}}, {"SLASH_SLASH", {true, 26}}, {"PCT", {true, 26}}, {"CARET", {true, 26}}, {"EXCL", {true, 26}}, {"RPAREN", {true, 26}}, {"COMMA", {true, 26}}, {"EOF_", {true, 26}}}},
	{18, {{"exprn", {false, 47}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{20, {{"expr1", {false, 23}}, {"expr13", {false, 7}}, {"expr12", {false, 8}}, {"expr11", {false, 9}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{21, {{"expr1", {false, 53}}, {"expr13", {false, 7}}, {"expr12", {false, 8}}, {"expr11", {false, 9}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{22, {{"expr1", {false, 77}}, {"expr13", {false, 7}}, {"expr12", {false, 8}}, {"expr11", {false, 9}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{23, {{"PIPE", {true, 1}}, {"RPAREN", {true, 1}}, {"COMMA", {true, 1}}, {"EOF_", {true, 1}}}},
	{24, {{"expr", {false, 51}}, {"lvalue", {false, 4}}, {"expr1", {false, 5}}, {"LPAREN", {true, 36}}, {"expr13", {false, 7}}, {"expr12", {false, 8}}, {"expr11", {false, 9}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"multiid", {false, 16}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{25, {{"FALSE_", {true, 34}}, {"ID", {true, 34}}, {"LPAREN", {true, 34}}, {"NONE_", {true, 34}}, {"NUM", {true, 34}}, {"PIPE", {true, 34}}, {"TRUE_", {true, 34}}, {"X", {true, 34}}, {"Y", {true, 34}}, {"AMP", {true, 34}}, {"CARET_PIPE", {true, 34}}, {"GT_GT", {true, 34}}, {"LT_LT", {true, 34}}, {"MINUS", {true, 34}}, {"PCT", {true, 34}}, {"PLUS", {true, 34}}, {"SLASH", {true, 34}}, {"SLASH_SLASH", {true, 34}}, {"STAR", {true, 34}}, {"CARET", {true, 34}}, {"EXCL", {true, 34}}, {"RPAREN", {true, 34}}, {"COMMA", {true, 34}}, {"EOF_", {true, 34}}}},
	{26, {{"expr12", {false, 27}}, {"expr11", {false, 9}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{27, {{"CARET_PIPE", {false, 28}}, {"PIPE", {true, 6}}, {"RPAREN", {true, 6}}, {"COMMA", {true, 6}}, {"EOF_", {true, 6}}}},
	{28, {{"expr11", {false, 29}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{29, {{"AMP", {false, 30}}, {"PIPE", {true, 8}}, {"CARET_PIPE", {true, 8}}, {"RPAREN", {true, 8}}, {"COMMA", {true, 8}}, {"EOF_", {true, 8}}}},
	{30, {{"expr7", {false, 31}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{31, {{"LT_LT", {false, 32}}, {"GT_GT", {false, 33}}, {"CARET_PIPE", {true, 10}}, {"PIPE", {true, 10}}, {"AMP", {true, 10}}, {"RPAREN", {true, 10}}, {"COMMA", {true, 10}}, {"EOF_", {true, 10}}}},
	{32, {{"expr6", {false, 34}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{33, {{"expr6", {false, 54}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{34, {{"PLUS", {false, 35}}, {"MINUS", {false, 36}}, {"AMP", {true, 12}}, {"CARET_PIPE", {true, 12}}, {"PIPE", {true, 12}}, {"LT_LT", {true, 12}}, {"GT_GT", {true, 12}}, {"RPAREN", {true, 12}}, {"COMMA", {true, 12}}, {"EOF_", {true, 12}}}},
	{35, {{"expr5", {false, 37}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{36, {{"expr5", {false, 55}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{37, {{"STAR", {false, 38}}, {"SLASH", {false, 39}}, {"SLASH_SLASH", {false, 40}}, {"PCT", {false, 41}}, {"AMP", {true, 15}}, {"CARET_PIPE", {true, 15}}, {"LT_LT", {true, 15}}, {"PIPE", {true, 15}}, {"GT_GT", {true, 15}}, {"PLUS", {true, 15}}, {"MINUS", {true, 15}}, {"RPAREN", {true, 15}}, {"COMMA", {true, 15}}, {"EOF_", {true, 15}}}},
	{38, {{"expr4", {false, 42}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"exprn", {false, 43}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{39, {{"expr4", {false, 56}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"exprn", {false, 43}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{40, {{"expr4", {false, 58}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"exprn", {false, 43}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{41, {{"expr4", {false, 76}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"exprn", {false, 43}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{42, {{"CARET", {false, 44}}, {"EXCL", {false, 45}}, {"AMP", {true, 18}}, {"CARET_PIPE", {true, 18}}, {"GT_GT", {true, 18}}, {"LT_LT", {true, 18}}, {"PIPE", {true, 18}}, {"PLUS", {true, 18}}, {"MINUS", {true, 18}}, {"STAR", {true, 18}}, {"SLASH", {true, 18}}, {"SLASH_SLASH", {true, 18}}, {"PCT", {true, 18}}, {"RPAREN", {true, 18}}, {"COMMA", {true, 18}}, {"EOF_", {true, 18}}}},
	{43, {{"AMP", {true, 28}}, {"CARET", {true, 28}}, {"CARET_PIPE", {true, 28}}, {"GT_GT", {true, 28}}, {"LT_LT", {true, 28}}, {"MINUS", {true, 28}}, {"PCT", {true, 28}}, {"PIPE", {true, 28}}, {"PLUS", {true, 28}}, {"SLASH", {true, 28}}, {"SLASH_SLASH", {true, 28}}, {"STAR", {true, 28}}, {"EXCL", {true, 28}}, {"RPAREN", {true, 28}}, {"COMMA", {true, 28}}, {"EOF_", {true, 28}}}},
	{44, {{"expr3", {false, 46}}, {"TILDE", {false, 18}}, {"exprn", {false, 43}}, {"PIPE", {false, 15}}, {"LPAREN", {true, 36}}, {"multiid", {false, 16}}, {"lvalue", {false, 25}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{45, {{"AMP", {true, 25}}, {"CARET_PIPE", {true, 25}}, {"GT_GT", {true, 25}}, {"LT_LT", {true, 25}}, {"MINUS", {true, 25}}, {"PIPE", {true, 25}}, {"PLUS", {true, 25}}, {"STAR", {true, 25}}, {"SLASH", {true, 25}}, {"SLASH_SLASH", {true, 25}}, {"PCT", {true, 25}}, {"CARET", {true, 25}}, {"EXCL", {true, 25}}, {"RPAREN", {true, 25}}, {"COMMA", {true, 25}}, {"EOF_", {true, 25}}}},
	{46, {{"AMP", {true, 24}}, {"CARET_PIPE", {true, 24}}, {"GT_GT", {true, 24}}, {"LT_LT", {true, 24}}, {"MINUS", {true, 24}}, {"PIPE", {true, 24}}, {"PLUS", {true, 24}}, {"STAR", {true, 24}}, {"SLASH", {true, 24}}, {"SLASH_SLASH", {true, 24}}, {"PCT", {true, 24}}, {"CARET", {true, 24}}, {"EXCL", {true, 24}}, {"RPAREN", {true, 24}}, {"COMMA", {true, 24}}, {"EOF_", {true, 24}}}},
	{47, {{"AMP", {true, 27}}, {"CARET", {true, 27}}, {"CARET_PIPE", {true, 27}}, {"GT_GT", {true, 27}}, {"LT_LT", {true, 27}}, {"MINUS", {true, 27}}, {"PCT", {true, 27}}, {"PIPE", {true, 27}}, {"PLUS", {true, 27}}, {"SLASH", {true, 27}}, {"SLASH_SLASH", {true, 27}}, {"STAR", {true, 27}}, {"EXCL", {true, 27}}, {"RPAREN", {true, 27}}, {"COMMA", {true, 27}}, {"EOF_", {true, 27}}}},
	{48, {{"PIPE", {false, 49}}}},
	{49, {{"FALSE_", {true, 29}}, {"ID", {true, 29}}, {"LPAREN", {true, 29}}, {"NONE_", {true, 29}}, {"NUM", {true, 29}}, {"PIPE", {true, 29}}, {"TRUE_", {true, 29}}, {"X", {true, 29}}, {"Y", {true, 29}}, {"AMP", {true, 29}}, {"CARET_PIPE", {true, 29}}, {"GT_GT", {true, 29}}, {"LT_LT", {true, 29}}, {"MINUS", {true, 29}}, {"PCT", {true, 29}}, {"PLUS", {true, 29}}, {"SLASH", {true, 29}}, {"SLASH_SLASH", {true, 29}}, {"STAR", {true, 29}}, {"CARET", {true, 29}}, {"EXCL", {true, 29}}, {"RPAREN", {true, 29}}, {"COMMA", {true, 29}}, {"EOF_", {true, 29}}}},
	{50, {{"RPAREN", {false, 52}}, {"COLON_EQUALS", {false, 21}}, {"L_ARROW", {false, 22}}}},
	{51, {{"RPAREN", {false, 57}}}},
	{52, {{"EQUALS", {true, 43}}, {"COLON_EQUALS", {true, 43}}, {"L_ARROW", {true, 43}}, {"AMP", {true, 43}}, {"CARET", {true, 43}}, {"CARET_PIPE", {true, 43}}, {"EXCL", {true, 43}}, {"FALSE_", {true, 43}}, {"GT_GT", {true, 43}}, {"ID", {true, 43}}, {"LPAREN", {true, 43}}, {"LT_LT", {true, 43}}, {"MINUS", {true, 43}}, {"NONE_", {true, 43}}, {"NUM", {true, 43}}, {"PCT", {true, 43}}, {"PIPE", {true, 43}}, {"PLUS", {true, 43}}, {"RPAREN", {true, 43}}, {"SLASH", {true, 43}}, {"SLASH_SLASH", {true, 43}}, {"STAR", {true, 43}}, {"TRUE_", {true, 43}}, {"X", {true, 43}}, {"Y", {true, 43}}, {"COMMA", {true, 43}}, {"EOF_", {true, 43}}}},
	{53, {{"PIPE", {true, 2}}, {"RPAREN", {true, 2}}, {"COMMA", {true, 2}}, {"EOF_", {true, 2}}}},
	{54, {{"PLUS", {false, 35}}, {"MINUS", {false, 36}}, {"AMP", {true, 13}}, {"CARET_PIPE", {true, 13}}, {"PIPE", {true, 13}}, {"LT_LT", {true, 13}}, {"GT_GT", {true, 13}}, {"RPAREN", {true, 13}}, {"COMMA", {true, 13}}, {"EOF_", {true, 13}}}},
	{55, {{"STAR", {false, 38}}, {"SLASH", {false, 39}}, {"SLASH_SLASH", {false, 40}}, {"PCT", {false, 41}}, {"AMP", {true, 16}}, {"CARET_PIPE", {true, 16}}, {"LT_LT", {true, 16}}, {"PIPE", {true, 16}}, {"GT_GT", {true, 16}}, {"PLUS", {true, 16}}, {"MINUS", {true, 16}}, {"RPAREN", {true, 16}}, {"COMMA", {true, 16}}, {"EOF_", {true, 16}}}},
	{56, {{"CARET", {false, 44}}, {"EXCL", {false, 45}}, {"AMP", {true, 19}}, {"CARET_PIPE", {true, 19}}, {"GT_GT", {true, 19}}, {"LT_LT", {true, 19}}, {"PIPE", {true, 19}}, {"PLUS", {true, 19}}, {"MINUS", {true, 19}}, {"STAR", {true, 19}}, {"SLASH", {true, 19}}, {"SLASH_SLASH", {true, 19}}, {"PCT", {true, 19}}, {"RPAREN", {true, 19}}, {"COMMA", {true, 19}}, {"EOF_", {true, 19}}}},
	{57, {{"FALSE_", {true, 30}}, {"ID", {true, 30}}, {"LPAREN", {true, 30}}, {"NONE_", {true, 30}}, {"NUM", {true, 30}}, {"PIPE", {true, 30}}, {"TRUE_", {true, 30}}, {"X", {true, 30}}, {"Y", {true, 30}}, {"AMP", {true, 30}}, {"CARET_PIPE", {true, 30}}, {"GT_GT", {true, 30}}, {"LT_LT", {true, 30}}, {"MINUS", {true, 30}}, {"PCT", {true, 30}}, {"PLUS", {true, 30}}, {"SLASH", {true, 30}}, {"SLASH_SLASH", {true, 30}}, {"STAR", {true, 30}}, {"CARET", {true, 30}}, {"EXCL", {true, 30}}, {"RPAREN", {true, 30}}, {"COMMA", {true, 30}}, {"EOF_", {true, 30}}}},
	{58, {{"CARET", {false, 44}}, {"EXCL", {false, 45}}, {"AMP", {true, 20}}, {"CARET_PIPE", {true, 20}}, {"GT_GT", {true, 20}}, {"LT_LT", {true, 20}}, {"PIPE", {true, 20}}, {"PLUS", {true, 20}}, {"MINUS", {true, 20}}, {"STAR", {true, 20}}, {"SLASH", {true, 20}}, {"SLASH_SLASH", {true, 20}}, {"PCT", {true, 20}}, {"RPAREN", {true, 20}}, {"COMMA", {true, 20}}, {"EOF_", {true, 20}}}},
	{59, {{"RPAREN", {false, 68}}, {"arglist", {false, 69}}, {"expr", {false, 70}}, {"lvalue", {false, 4}}, {"expr1", {false, 5}}, {"LPAREN", {true, 36}}, {"expr13", {false, 7}}, {"expr12", {false, 8}}, {"expr11", {false, 9}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"multiid", {false, 71}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{60, {{"FALSE_", {true, 33}}, {"ID", {true, 33}}, {"LPAREN", {true, 33}}, {"NONE_", {true, 33}}, {"NUM", {true, 33}}, {"PIPE", {true, 33}}, {"TRUE_", {true, 33}}, {"X", {true, 33}}, {"Y", {true, 33}}, {"AMP", {true, 33}}, {"CARET_PIPE", {true, 33}}, {"GT_GT", {true, 33}}, {"LT_LT", {true, 33}}, {"MINUS", {true, 33}}, {"PCT", {true, 33}}, {"PLUS", {true, 33}}, {"SLASH", {true, 33}}, {"SLASH_SLASH", {true, 33}}, {"STAR", {true, 33}}, {"CARET", {true, 33}}, {"EXCL", {true, 33}}, {"RPAREN", {true, 33}}, {"COMMA", {true, 33}}, {"EOF_", {true, 33}}}},
	{61, {{"LPAREN", {true, 35}}, {"FALSE_", {true, 35}}, {"NONE_", {true, 35}}, {"NUM", {true, 35}}, {"TRUE_", {true, 35}}, {"X", {true, 35}}, {"Y", {true, 35}}, {"ID", {true, 35}}}},
	{62, {{"AMP", {true, 37}}, {"CARET", {true, 37}}, {"CARET_PIPE", {true, 37}}, {"EXCL", {true, 37}}, {"FALSE_", {true, 37}}, {"GT_GT", {true, 37}}, {"ID", {true, 37}}, {"LPAREN", {true, 37}}, {"LT_LT", {true, 37}}, {"MINUS", {true, 37}}, {"NONE_", {true, 37}}, {"NUM", {true, 37}}, {"PCT", {true, 37}}, {"PIPE", {true, 37}}, {"PLUS", {true, 37}}, {"RPAREN", {true, 37}}, {"SLASH", {true, 37}}, {"SLASH_SLASH", {true, 37}}, {"STAR", {true, 37}}, {"TRUE_", {true, 37}}, {"X", {true, 37}}, {"Y", {true, 37}}, {"COMMA", {true, 37}}, {"EOF_", {true, 37}}}},
	{63, {{"AMP", {true, 38}}, {"CARET", {true, 38}}, {"CARET_PIPE", {true, 38}}, {"EXCL", {true, 38}}, {"FALSE_", {true, 38}}, {"GT_GT", {true, 38}}, {"ID", {true, 38}}, {"LPAREN", {true, 38}}, {"LT_LT", {true, 38}}, {"MINUS", {true, 38}}, {"NONE_", {true, 38}}, {"NUM", {true, 38}}, {"PCT", {true, 38}}, {"PIPE", {true, 38}}, {"PLUS", {true, 38}}, {"RPAREN", {true, 38}}, {"SLASH", {true, 38}}, {"SLASH_SLASH", {true, 38}}, {"STAR", {true, 38}}, {"TRUE_", {true, 38}}, {"X", {true, 38}}, {"Y", {true, 38}}, {"COMMA", {true, 38}}, {"EOF_", {true, 38}}}},
	{64, {{"AMP", {true, 39}}, {"CARET", {true, 39}}, {"CARET_PIPE", {true, 39}}, {"EXCL", {true, 39}}, {"FALSE_", {true, 39}}, {"GT_GT", {true, 39}}, {"ID", {true, 39}}, {"LPAREN", {true, 39}}, {"LT_LT", {true, 39}}, {"MINUS", {true, 39}}, {"NONE_", {true, 39}}, {"NUM", {true, 39}}, {"PCT", {true, 39}}, {"PIPE", {true, 39}}, {"PLUS", {true, 39}}, {"RPAREN", {true, 39}}, {"SLASH", {true, 39}}, {"SLASH_SLASH", {true, 39}}, {"STAR", {true, 39}}, {"TRUE_", {true, 39}}, {"X", {true, 39}}, {"Y", {true, 39}}, {"COMMA", {true, 39}}, {"EOF_", {true, 39}}}},
	{65, {{"AMP", {true, 40}}, {"CARET", {true, 40}}, {"CARET_PIPE", {true, 40}}, {"EXCL", {true, 40}}, {"FALSE_", {true, 40}}, {"GT_GT", {true, 40}}, {"ID", {true, 40}}, {"LPAREN", {true, 40}}, {"LT_LT", {true, 40}}, {"MINUS", {true, 40}}, {"NONE_", {true, 40}}, {"NUM", {true, 40}}, {"PCT", {true, 40}}, {"PIPE", {true, 40}}, {"PLUS", {true, 40}}, {"RPAREN", {true, 40}}, {"SLASH", {true, 40}}, {"SLASH_SLASH", {true, 40}}, {"STAR", {true, 40}}, {"TRUE_", {true, 40}}, {"X", {true, 40}}, {"Y", {true, 40}}, {"COMMA", {true, 40}}, {"EOF_", {true, 40}}}},
	{66, {{"AMP", {true, 41}}, {"CARET", {true, 41}}, {"CARET_PIPE", {true, 41}}, {"EXCL", {true, 41}}, {"FALSE_", {true, 41}}, {"GT_GT", {true, 41}}, {"ID", {true, 41}}, {"LPAREN", {true, 41}}, {"LT_LT", {true, 41}}, {"MINUS", {true, 41}}, {"NONE_", {true, 41}}, {"NUM", {true, 41}}, {"PCT", {true, 41}}, {"PIPE", {true, 41}}, {"PLUS", {true, 41}}, {"RPAREN", {true, 41}}, {"SLASH", {true, 41}}, {"SLASH_SLASH", {true, 41}}, {"STAR", {true, 41}}, {"TRUE_", {true, 41}}, {"X", {true, 41}}, {"Y", {true, 41}}, {"COMMA", {true, 41}}, {"EOF_", {true, 41}}}},
	{67, {{"AMP", {true, 42}}, {"CARET", {true, 42}}, {"CARET_PIPE", {true, 42}}, {"EXCL", {true, 42}}, {"FALSE_", {true, 42}}, {"GT_GT", {true, 42}}, {"ID", {true, 42}}, {"LPAREN", {true, 42}}, {"LT_LT", {true, 42}}, {"MINUS", {true, 42}}, {"NONE_", {true, 42}}, {"NUM", {true, 42}}, {"PCT", {true, 42}}, {"PIPE", {true, 42}}, {"PLUS", {true, 42}}, {"RPAREN", {true, 42}}, {"SLASH", {true, 42}}, {"SLASH_SLASH", {true, 42}}, {"STAR", {true, 42}}, {"TRUE_", {true, 42}}, {"X", {true, 42}}, {"Y", {true, 42}}, {"COMMA", {true, 42}}, {"EOF_", {true, 42}}}},
	{68, {{"FALSE_", {true, 31}}, {"ID", {true, 31}}, {"LPAREN", {true, 31}}, {"NONE_", {true, 31}}, {"NUM", {true, 31}}, {"PIPE", {true, 31}}, {"TRUE_", {true, 31}}, {"X", {true, 31}}, {"Y", {true, 31}}, {"AMP", {true, 31}}, {"CARET_PIPE", {true, 31}}, {"GT_GT", {true, 31}}, {"LT_LT", {true, 31}}, {"MINUS", {true, 31}}, {"PCT", {true, 31}}, {"PLUS", {true, 31}}, {"SLASH", {true, 31}}, {"SLASH_SLASH", {true, 31}}, {"STAR", {true, 31}}, {"CARET", {true, 31}}, {"EXCL", {true, 31}}, {"RPAREN", {true, 31}}, {"COMMA", {true, 31}}, {"EOF_", {true, 31}}}},
	{69, {{"RPAREN", {false, 72}}}},
	{70, {{"COMMA", {false, 73}}, {"RPAREN", {true, 44}}}},
	{71, {{"factor", {false, 60}}, {"ID", {false, 61}}, {"NUM", {false, 62}}, {"X", {false, 63}}, {"Y", {false, 64}}, {"NONE_", {false, 65}}, {"TRUE_", {false, 66}}, {"FALSE_", {false, 67}}}},
	{72, {{"FALSE_", {true, 32}}, {"ID", {true, 32}}, {"LPAREN", {true, 32}}, {"NONE_", {true, 32}}, {"NUM", {true, 32}}, {"PIPE", {true, 32}}, {"TRUE_", {true, 32}}, {"X", {true, 32}}, {"Y", {true, 32}}, {"AMP", {true, 32}}, {"CARET_PIPE", {true, 32}}, {"GT_GT", {true, 32}}, {"LT_LT", {true, 32}}, {"MINUS", {true, 32}}, {"PCT", {true, 32}}, {"PLUS", {true, 32}}, {"SLASH", {true, 32}}, {"SLASH_SLASH", {true, 32}}, {"STAR", {true, 32}}, {"CARET", {true, 32}}, {"EXCL", {true, 32}}, {"RPAREN", {true, 32}}, {"COMMA", {true, 32}}, {"EOF_", {true, 32}}}},
	{73, {{"arglist", {false, 74}}, {"expr", {false, 70}}, {"lvalue", {false, 4}}, {"expr1", {false, 5}}, {"LPAREN", {true, 36}}, {"expr13", {false, 7}}, {"expr12", {false, 8}}, {"expr11", {false, 9}}, {"expr7", {false, 10}}, {"expr6", {false, 11}}, {"expr5", {false, 12}}, {"exprn", {false, 13}}, {"expr4", {false, 14}}, {"PIPE", {false, 15}}, {"multiid", {false, 16}}, {"expr3", {false, 17}}, {"TILDE", {false, 18}}, {"FALSE_", {true, 36}}, {"NONE_", {true, 36}}, {"NUM", {true, 36}}, {"TRUE_", {true, 36}}, {"X", {true, 36}}, {"Y", {true, 36}}, {"ID", {true, 36}}}},
	{74, {{"RPAREN", {true, 45}}}},
	{75, {{"AMP", {true, 22}}, {"CARET_PIPE", {true, 22}}, {"GT_GT", {true, 22}}, {"LT_LT", {true, 22}}, {"PIPE", {true, 22}}, {"PLUS", {true, 22}}, {"MINUS", {true, 22}}, {"STAR", {true, 22}}, {"SLASH", {true, 22}}, {"SLASH_SLASH", {true, 22}}, {"PCT", {true, 22}}, {"RPAREN", {true, 22}}, {"COMMA", {true, 22}}, {"EOF_", {true, 22}}}},
	{76, {{"CARET", {false, 44}}, {"EXCL", {false, 45}}, {"AMP", {true, 21}}, {"CARET_PIPE", {true, 21}}, {"GT_GT", {true, 21}}, {"LT_LT", {true, 21}}, {"PIPE", {true, 21}}, {"PLUS", {true, 21}}, {"MINUS", {true, 21}}, {"STAR", {true, 21}}, {"SLASH", {true, 21}}, {"SLASH_SLASH", {true, 21}}, {"PCT", {true, 21}}, {"RPAREN", {true, 21}}, {"COMMA", {true, 21}}, {"EOF_", {true, 21}}}},
	{77, {{"PIPE", {true, 3}}, {"RPAREN", {true, 3}}, {"COMMA", {true, 3}}, {"EOF_", {true, 3}}}}
});