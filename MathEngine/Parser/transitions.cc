
#include "transitions.h"

using namespace std;

#ifndef __TERMINALS__
#define __TERMINALS__

// enum Terminal {
//     {terminal_enums}
// };

const unordered_set<string> terminals ({
    "AMP", "APOSTROPHE", "BACKSLASH", "BACKTICK", "BOF_", "C", "CARET",
    "CARET_PIPE", "COLON", "COLON_EQUALS", "COMMA", "DOLLAR", "DOT", "EOF_",
    "EQUALS", "EXCL", "FALSE_", "GT_GT", "HEX", "ID", "LBRACE", "LPAREN", "LSQUARE",
    "LT_LT", "L_ARROW", "MINUS", "NONE_", "NULL_", "NUM", "P", "PCT", "PIPE",
    "PLUS", "POUND", "QUESTION", "QUOTE", "RBRACE", "RPAREN", "RSQUARE", "R_ARROW",
    "SEMICOLON", "SLASH", "SLASH_SLASH", "STAR", "STAR_STAR", "STR", "TILDE",
    "TRUE_", "UNDERSCORE", "X", "Y"
});

#endif // __TERMINALS__


#ifndef __NONTERMINALS__
#define __NONTERMINALS__

// enum NonTerminal {
//     {nonterminal_enums}
// };

const unordered_set<string> nonterminals ({
    "arglist", "expr", "expr1", "expr11", "expr12", "expr13", "expr3", "expr4",
    "expr5", "expr6", "expr7", "exprn", "factor", "lvalue", "statement"
});

#endif // __NONTERMINALS__

#ifndef __RULES__
#define __RULES__

// enum Rules {
//     {rule_enums}
// };

const vector<list<string>> rules ({
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
	{"expr5", "expr5", "C", "expr4"},
	{"expr5", "expr5", "P", "expr4"},
	{"expr5", "expr4"},
	{"expr4", "expr4", "CARET", "expr3"},
	{"expr4", "expr4", "STAR_STAR", "expr3"},
	{"expr4", "expr4", "EXCL"},
	{"expr4", "expr3"},
	{"expr3", "TILDE", "exprn"},
	{"expr3", "exprn"},
	{"exprn", "ID", "exprn"},
	{"exprn", "ID", "LPAREN", "arglist", "RPAREN"},
	{"exprn", "factor"},
	{"exprn", "lvalue"},
	{"factor", "NUM"},
	{"factor", "X"},
	{"factor", "Y"},
	{"factor", "NONE_"},
	{"factor", "TRUE_"},
	{"factor", "FALSE_"},
	{"factor", "PIPE", "expr", "PIPE"},
	{"factor", "LPAREN", "expr", "RPAREN"},
	{"lvalue", "LPAREN", "lvalue", "RPAREN"},
	{"arglist"},
	{"arglist", "expr"},
	{"arglist", "expr", "COMMA", "arglist"},
	{"start", "BOF_", "statement", "EOF_"}
});

#endif // __RULES__

const vector<unordered_map<string, pair<bool, int>>> transitions ({
	/* State 0 */ {{"BOF_", {0, 1}}},
	/* State 1 */ {{"statement", {0, 2}}, {"expr", {0, 3}}, {"lvalue", {0, 4}}, {"expr1", {0, 5}}, {"LPAREN", {0, 6}}, {"expr13", {0, 7}}, {"expr12", {0, 8}}, {"expr11", {0, 9}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}},
	/* State 2 */ {{"EOF_", {0, 26}}},
	/* State 3 */ {{"EOF_", {1, 0}}},
	/* State 4 */ {{"EQUALS", {0, 27}}, {"COLON_EQUALS", {0, 28}}, {"L_ARROW", {0, 29}}, {"AMP", {1, 34}}, {"C", {1, 34}}, {"CARET", {1, 34}}, {"CARET_PIPE", {1, 34}}, {"EXCL", {1, 34}}, {"GT_GT", {1, 34}}, {"LT_LT", {1, 34}}, {"MINUS", {1, 34}}, {"P", {1, 34}}, {"PCT", {1, 34}}, {"PIPE", {1, 34}}, {"PLUS", {1, 34}}, {"SLASH", {1, 34}}, {"SLASH_SLASH", {1, 34}}, {"STAR", {1, 34}}, {"STAR_STAR", {1, 34}}, {"RPAREN", {1, 34}}, {"COMMA", {1, 34}}, {"EOF_", {1, 34}}},
	/* State 5 */ {{"PIPE", {1, 4}}, {"RPAREN", {1, 4}}, {"COMMA", {1, 4}}, {"EOF_", {1, 4}}},
	/* State 6 */ {{"lvalue", {0, 64}}, {"expr", {0, 65}}, {"LPAREN", {0, 6}}, {"expr1", {0, 5}}, {"expr13", {0, 7}}, {"expr12", {0, 8}}, {"expr11", {0, 9}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}},
	/* State 7 */ {{"PIPE", {1, 5}}, {"RPAREN", {1, 5}}, {"COMMA", {1, 5}}, {"EOF_", {1, 5}}},
	/* State 8 */ {{"CARET_PIPE", {0, 35}}, {"PIPE", {1, 7}}, {"RPAREN", {1, 7}}, {"COMMA", {1, 7}}, {"EOF_", {1, 7}}},
	/* State 9 */ {{"AMP", {0, 37}}, {"PIPE", {1, 9}}, {"CARET_PIPE", {1, 9}}, {"RPAREN", {1, 9}}, {"COMMA", {1, 9}}, {"EOF_", {1, 9}}},
	/* State 10 */ {{"LT_LT", {0, 39}}, {"GT_GT", {0, 40}}, {"CARET_PIPE", {1, 11}}, {"PIPE", {1, 11}}, {"AMP", {1, 11}}, {"RPAREN", {1, 11}}, {"COMMA", {1, 11}}, {"EOF_", {1, 11}}},
	/* State 11 */ {{"PLUS", {0, 42}}, {"MINUS", {0, 43}}, {"AMP", {1, 14}}, {"CARET_PIPE", {1, 14}}, {"PIPE", {1, 14}}, {"LT_LT", {1, 14}}, {"GT_GT", {1, 14}}, {"RPAREN", {1, 14}}, {"COMMA", {1, 14}}, {"EOF_", {1, 14}}},
	/* State 12 */ {{"STAR", {0, 45}}, {"SLASH", {0, 46}}, {"SLASH_SLASH", {0, 47}}, {"PCT", {0, 48}}, {"C", {0, 49}}, {"P", {0, 50}}, {"AMP", {1, 17}}, {"CARET_PIPE", {1, 17}}, {"LT_LT", {1, 17}}, {"PIPE", {1, 17}}, {"GT_GT", {1, 17}}, {"PLUS", {1, 17}}, {"MINUS", {1, 17}}, {"RPAREN", {1, 17}}, {"COMMA", {1, 17}}, {"EOF_", {1, 17}}},
	/* State 13 */ {{"CARET", {0, 52}}, {"STAR_STAR", {0, 53}}, {"EXCL", {0, 54}}, {"AMP", {1, 24}}, {"CARET_PIPE", {1, 24}}, {"GT_GT", {1, 24}}, {"LT_LT", {1, 24}}, {"PIPE", {1, 24}}, {"PLUS", {1, 24}}, {"MINUS", {1, 24}}, {"STAR", {1, 24}}, {"SLASH", {1, 24}}, {"SLASH_SLASH", {1, 24}}, {"PCT", {1, 24}}, {"C", {1, 24}}, {"P", {1, 24}}, {"RPAREN", {1, 24}}, {"COMMA", {1, 24}}, {"EOF_", {1, 24}}},
	/* State 14 */ {{"AMP", {1, 28}}, {"CARET_PIPE", {1, 28}}, {"GT_GT", {1, 28}}, {"LT_LT", {1, 28}}, {"MINUS", {1, 28}}, {"PIPE", {1, 28}}, {"PLUS", {1, 28}}, {"STAR", {1, 28}}, {"SLASH", {1, 28}}, {"SLASH_SLASH", {1, 28}}, {"PCT", {1, 28}}, {"C", {1, 28}}, {"P", {1, 28}}, {"CARET", {1, 28}}, {"STAR_STAR", {1, 28}}, {"EXCL", {1, 28}}, {"RPAREN", {1, 28}}, {"COMMA", {1, 28}}, {"EOF_", {1, 28}}},
	/* State 15 */ {{"exprn", {0, 56}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 16 */ {{"AMP", {1, 30}}, {"C", {1, 30}}, {"CARET", {1, 30}}, {"CARET_PIPE", {1, 30}}, {"GT_GT", {1, 30}}, {"LT_LT", {1, 30}}, {"MINUS", {1, 30}}, {"P", {1, 30}}, {"PCT", {1, 30}}, {"PIPE", {1, 30}}, {"PLUS", {1, 30}}, {"SLASH", {1, 30}}, {"SLASH_SLASH", {1, 30}}, {"STAR", {1, 30}}, {"STAR_STAR", {1, 30}}, {"EXCL", {1, 30}}, {"RPAREN", {1, 30}}, {"COMMA", {1, 30}}, {"EOF_", {1, 30}}},
	/* State 17 */ {{"exprn", {0, 57}}, {"LPAREN", {0, 58}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}},
	/* State 18 */ {{"AMP", {1, 33}}, {"C", {1, 33}}, {"CARET", {1, 33}}, {"CARET_PIPE", {1, 33}}, {"EXCL", {1, 33}}, {"GT_GT", {1, 33}}, {"LT_LT", {1, 33}}, {"MINUS", {1, 33}}, {"P", {1, 33}}, {"PCT", {1, 33}}, {"PIPE", {1, 33}}, {"PLUS", {1, 33}}, {"SLASH", {1, 33}}, {"SLASH_SLASH", {1, 33}}, {"STAR", {1, 33}}, {"STAR_STAR", {1, 33}}, {"RPAREN", {1, 33}}, {"COMMA", {1, 33}}, {"EOF_", {1, 33}}},
	/* State 19 */ {{"AMP", {1, 35}}, {"C", {1, 35}}, {"CARET", {1, 35}}, {"CARET_PIPE", {1, 35}}, {"EXCL", {1, 35}}, {"GT_GT", {1, 35}}, {"LT_LT", {1, 35}}, {"MINUS", {1, 35}}, {"P", {1, 35}}, {"PCT", {1, 35}}, {"PIPE", {1, 35}}, {"PLUS", {1, 35}}, {"SLASH", {1, 35}}, {"SLASH_SLASH", {1, 35}}, {"STAR", {1, 35}}, {"STAR_STAR", {1, 35}}, {"RPAREN", {1, 35}}, {"COMMA", {1, 35}}, {"EOF_", {1, 35}}},
	/* State 20 */ {{"AMP", {1, 36}}, {"C", {1, 36}}, {"CARET", {1, 36}}, {"CARET_PIPE", {1, 36}}, {"EXCL", {1, 36}}, {"GT_GT", {1, 36}}, {"LT_LT", {1, 36}}, {"MINUS", {1, 36}}, {"P", {1, 36}}, {"PCT", {1, 36}}, {"PIPE", {1, 36}}, {"PLUS", {1, 36}}, {"SLASH", {1, 36}}, {"SLASH_SLASH", {1, 36}}, {"STAR", {1, 36}}, {"STAR_STAR", {1, 36}}, {"RPAREN", {1, 36}}, {"COMMA", {1, 36}}, {"EOF_", {1, 36}}},
	/* State 21 */ {{"AMP", {1, 37}}, {"C", {1, 37}}, {"CARET", {1, 37}}, {"CARET_PIPE", {1, 37}}, {"EXCL", {1, 37}}, {"GT_GT", {1, 37}}, {"LT_LT", {1, 37}}, {"MINUS", {1, 37}}, {"P", {1, 37}}, {"PCT", {1, 37}}, {"PIPE", {1, 37}}, {"PLUS", {1, 37}}, {"SLASH", {1, 37}}, {"SLASH_SLASH", {1, 37}}, {"STAR", {1, 37}}, {"STAR_STAR", {1, 37}}, {"RPAREN", {1, 37}}, {"COMMA", {1, 37}}, {"EOF_", {1, 37}}},
	/* State 22 */ {{"AMP", {1, 38}}, {"C", {1, 38}}, {"CARET", {1, 38}}, {"CARET_PIPE", {1, 38}}, {"EXCL", {1, 38}}, {"GT_GT", {1, 38}}, {"LT_LT", {1, 38}}, {"MINUS", {1, 38}}, {"P", {1, 38}}, {"PCT", {1, 38}}, {"PIPE", {1, 38}}, {"PLUS", {1, 38}}, {"SLASH", {1, 38}}, {"SLASH_SLASH", {1, 38}}, {"STAR", {1, 38}}, {"STAR_STAR", {1, 38}}, {"RPAREN", {1, 38}}, {"COMMA", {1, 38}}, {"EOF_", {1, 38}}},
	/* State 23 */ {{"AMP", {1, 39}}, {"C", {1, 39}}, {"CARET", {1, 39}}, {"CARET_PIPE", {1, 39}}, {"EXCL", {1, 39}}, {"GT_GT", {1, 39}}, {"LT_LT", {1, 39}}, {"MINUS", {1, 39}}, {"P", {1, 39}}, {"PCT", {1, 39}}, {"PIPE", {1, 39}}, {"PLUS", {1, 39}}, {"SLASH", {1, 39}}, {"SLASH_SLASH", {1, 39}}, {"STAR", {1, 39}}, {"STAR_STAR", {1, 39}}, {"RPAREN", {1, 39}}, {"COMMA", {1, 39}}, {"EOF_", {1, 39}}},
	/* State 24 */ {{"AMP", {1, 40}}, {"C", {1, 40}}, {"CARET", {1, 40}}, {"CARET_PIPE", {1, 40}}, {"EXCL", {1, 40}}, {"GT_GT", {1, 40}}, {"LT_LT", {1, 40}}, {"MINUS", {1, 40}}, {"P", {1, 40}}, {"PCT", {1, 40}}, {"PIPE", {1, 40}}, {"PLUS", {1, 40}}, {"SLASH", {1, 40}}, {"SLASH_SLASH", {1, 40}}, {"STAR", {1, 40}}, {"STAR_STAR", {1, 40}}, {"RPAREN", {1, 40}}, {"COMMA", {1, 40}}, {"EOF_", {1, 40}}},
	/* State 25 */ {{"expr", {0, 72}}, {"lvalue", {0, 4}}, {"expr1", {0, 5}}, {"LPAREN", {0, 6}}, {"expr13", {0, 7}}, {"expr12", {0, 8}}, {"expr11", {0, 9}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}},
	/* State 26 */ {},
	/* State 27 */ {{"expr1", {0, 30}}, {"expr13", {0, 7}}, {"expr12", {0, 8}}, {"expr11", {0, 9}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 28 */ {{"expr1", {0, 67}}, {"expr13", {0, 7}}, {"expr12", {0, 8}}, {"expr11", {0, 9}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 29 */ {{"expr1", {0, 79}}, {"expr13", {0, 7}}, {"expr12", {0, 8}}, {"expr11", {0, 9}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 30 */ {{"PIPE", {1, 1}}, {"RPAREN", {1, 1}}, {"COMMA", {1, 1}}, {"EOF_", {1, 1}}},
	/* State 31 */ {{"AMP", {1, 34}}, {"C", {1, 34}}, {"CARET", {1, 34}}, {"CARET_PIPE", {1, 34}}, {"EXCL", {1, 34}}, {"GT_GT", {1, 34}}, {"LT_LT", {1, 34}}, {"MINUS", {1, 34}}, {"P", {1, 34}}, {"PCT", {1, 34}}, {"PIPE", {1, 34}}, {"PLUS", {1, 34}}, {"SLASH", {1, 34}}, {"SLASH_SLASH", {1, 34}}, {"STAR", {1, 34}}, {"STAR_STAR", {1, 34}}, {"RPAREN", {1, 34}}, {"COMMA", {1, 34}}, {"EOF_", {1, 34}}},
	/* State 32 */ {{"expr", {0, 65}}, {"lvalue", {0, 4}}, {"expr1", {0, 5}}, {"LPAREN", {0, 6}}, {"expr13", {0, 7}}, {"expr12", {0, 8}}, {"expr11", {0, 9}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}},
	/* State 33 */ {{"expr12", {0, 34}}, {"expr11", {0, 9}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 34 */ {{"CARET_PIPE", {0, 35}}, {"PIPE", {1, 6}}, {"RPAREN", {1, 6}}, {"COMMA", {1, 6}}, {"EOF_", {1, 6}}},
	/* State 35 */ {{"expr11", {0, 36}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 36 */ {{"AMP", {0, 37}}, {"PIPE", {1, 8}}, {"CARET_PIPE", {1, 8}}, {"RPAREN", {1, 8}}, {"COMMA", {1, 8}}, {"EOF_", {1, 8}}},
	/* State 37 */ {{"expr7", {0, 38}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 38 */ {{"LT_LT", {0, 39}}, {"GT_GT", {0, 40}}, {"CARET_PIPE", {1, 10}}, {"PIPE", {1, 10}}, {"AMP", {1, 10}}, {"RPAREN", {1, 10}}, {"COMMA", {1, 10}}, {"EOF_", {1, 10}}},
	/* State 39 */ {{"expr6", {0, 41}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 40 */ {{"expr6", {0, 68}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 41 */ {{"PLUS", {0, 42}}, {"MINUS", {0, 43}}, {"AMP", {1, 12}}, {"CARET_PIPE", {1, 12}}, {"PIPE", {1, 12}}, {"LT_LT", {1, 12}}, {"GT_GT", {1, 12}}, {"RPAREN", {1, 12}}, {"COMMA", {1, 12}}, {"EOF_", {1, 12}}},
	/* State 42 */ {{"expr5", {0, 44}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 43 */ {{"expr5", {0, 69}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 44 */ {{"STAR", {0, 45}}, {"SLASH", {0, 46}}, {"SLASH_SLASH", {0, 47}}, {"PCT", {0, 48}}, {"C", {0, 49}}, {"P", {0, 50}}, {"AMP", {1, 15}}, {"CARET_PIPE", {1, 15}}, {"LT_LT", {1, 15}}, {"PIPE", {1, 15}}, {"GT_GT", {1, 15}}, {"PLUS", {1, 15}}, {"MINUS", {1, 15}}, {"RPAREN", {1, 15}}, {"COMMA", {1, 15}}, {"EOF_", {1, 15}}},
	/* State 45 */ {{"expr4", {0, 51}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 46 */ {{"expr4", {0, 70}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 47 */ {{"expr4", {0, 74}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 48 */ {{"expr4", {0, 76}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 49 */ {{"expr4", {0, 77}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 50 */ {{"expr4", {0, 78}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 51 */ {{"CARET", {0, 52}}, {"STAR_STAR", {0, 53}}, {"EXCL", {0, 54}}, {"AMP", {1, 18}}, {"CARET_PIPE", {1, 18}}, {"GT_GT", {1, 18}}, {"LT_LT", {1, 18}}, {"PIPE", {1, 18}}, {"PLUS", {1, 18}}, {"MINUS", {1, 18}}, {"STAR", {1, 18}}, {"SLASH", {1, 18}}, {"SLASH_SLASH", {1, 18}}, {"PCT", {1, 18}}, {"C", {1, 18}}, {"P", {1, 18}}, {"RPAREN", {1, 18}}, {"COMMA", {1, 18}}, {"EOF_", {1, 18}}},
	/* State 52 */ {{"expr3", {0, 55}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 53 */ {{"expr3", {0, 71}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"lvalue", {0, 31}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"LPAREN", {0, 32}}},
	/* State 54 */ {{"AMP", {1, 27}}, {"CARET_PIPE", {1, 27}}, {"GT_GT", {1, 27}}, {"LT_LT", {1, 27}}, {"MINUS", {1, 27}}, {"PIPE", {1, 27}}, {"PLUS", {1, 27}}, {"STAR", {1, 27}}, {"SLASH", {1, 27}}, {"SLASH_SLASH", {1, 27}}, {"PCT", {1, 27}}, {"C", {1, 27}}, {"P", {1, 27}}, {"CARET", {1, 27}}, {"STAR_STAR", {1, 27}}, {"EXCL", {1, 27}}, {"RPAREN", {1, 27}}, {"COMMA", {1, 27}}, {"EOF_", {1, 27}}},
	/* State 55 */ {{"AMP", {1, 25}}, {"CARET_PIPE", {1, 25}}, {"GT_GT", {1, 25}}, {"LT_LT", {1, 25}}, {"MINUS", {1, 25}}, {"PIPE", {1, 25}}, {"PLUS", {1, 25}}, {"STAR", {1, 25}}, {"SLASH", {1, 25}}, {"SLASH_SLASH", {1, 25}}, {"PCT", {1, 25}}, {"C", {1, 25}}, {"P", {1, 25}}, {"CARET", {1, 25}}, {"STAR_STAR", {1, 25}}, {"EXCL", {1, 25}}, {"RPAREN", {1, 25}}, {"COMMA", {1, 25}}, {"EOF_", {1, 25}}},
	/* State 56 */ {{"AMP", {1, 29}}, {"C", {1, 29}}, {"CARET", {1, 29}}, {"CARET_PIPE", {1, 29}}, {"GT_GT", {1, 29}}, {"LT_LT", {1, 29}}, {"MINUS", {1, 29}}, {"P", {1, 29}}, {"PCT", {1, 29}}, {"PIPE", {1, 29}}, {"PLUS", {1, 29}}, {"SLASH", {1, 29}}, {"SLASH_SLASH", {1, 29}}, {"STAR", {1, 29}}, {"STAR_STAR", {1, 29}}, {"EXCL", {1, 29}}, {"RPAREN", {1, 29}}, {"COMMA", {1, 29}}, {"EOF_", {1, 29}}},
	/* State 57 */ {{"AMP", {1, 31}}, {"C", {1, 31}}, {"CARET", {1, 31}}, {"CARET_PIPE", {1, 31}}, {"EXCL", {1, 31}}, {"GT_GT", {1, 31}}, {"LT_LT", {1, 31}}, {"MINUS", {1, 31}}, {"P", {1, 31}}, {"PCT", {1, 31}}, {"PIPE", {1, 31}}, {"PLUS", {1, 31}}, {"SLASH", {1, 31}}, {"SLASH_SLASH", {1, 31}}, {"STAR", {1, 31}}, {"STAR_STAR", {1, 31}}, {"RPAREN", {1, 31}}, {"COMMA", {1, 31}}, {"EOF_", {1, 31}}},
	/* State 58 */ {{"arglist", {0, 59}}, {"expr", {0, 60}}, {"lvalue", {0, 4}}, {"expr1", {0, 5}}, {"LPAREN", {0, 6}}, {"expr13", {0, 7}}, {"expr12", {0, 8}}, {"expr11", {0, 9}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"RPAREN", {1, 44}}},
	/* State 59 */ {{"RPAREN", {0, 61}}},
	/* State 60 */ {{"COMMA", {0, 62}}, {"RPAREN", {1, 45}}},
	/* State 61 */ {{"AMP", {1, 32}}, {"C", {1, 32}}, {"CARET", {1, 32}}, {"CARET_PIPE", {1, 32}}, {"EXCL", {1, 32}}, {"GT_GT", {1, 32}}, {"LT_LT", {1, 32}}, {"MINUS", {1, 32}}, {"P", {1, 32}}, {"PCT", {1, 32}}, {"PIPE", {1, 32}}, {"PLUS", {1, 32}}, {"SLASH", {1, 32}}, {"SLASH_SLASH", {1, 32}}, {"STAR", {1, 32}}, {"STAR_STAR", {1, 32}}, {"RPAREN", {1, 32}}, {"COMMA", {1, 32}}, {"EOF_", {1, 32}}},
	/* State 62 */ {{"arglist", {0, 63}}, {"expr", {0, 60}}, {"lvalue", {0, 4}}, {"expr1", {0, 5}}, {"LPAREN", {0, 6}}, {"expr13", {0, 7}}, {"expr12", {0, 8}}, {"expr11", {0, 9}}, {"expr7", {0, 10}}, {"expr6", {0, 11}}, {"expr5", {0, 12}}, {"expr4", {0, 13}}, {"expr3", {0, 14}}, {"TILDE", {0, 15}}, {"exprn", {0, 16}}, {"ID", {0, 17}}, {"factor", {0, 18}}, {"NUM", {0, 19}}, {"X", {0, 20}}, {"Y", {0, 21}}, {"NONE_", {0, 22}}, {"TRUE_", {0, 23}}, {"FALSE_", {0, 24}}, {"PIPE", {0, 25}}, {"RPAREN", {1, 44}}},
	/* State 63 */ {{"RPAREN", {1, 46}}},
	/* State 64 */ {{"RPAREN", {0, 66}}, {"COLON_EQUALS", {0, 28}}, {"L_ARROW", {0, 29}}},
	/* State 65 */ {{"RPAREN", {0, 75}}},
	/* State 66 */ {{"EQUALS", {1, 43}}, {"COLON_EQUALS", {1, 43}}, {"L_ARROW", {1, 43}}, {"AMP", {1, 43}}, {"C", {1, 43}}, {"CARET", {1, 43}}, {"CARET_PIPE", {1, 43}}, {"EXCL", {1, 43}}, {"GT_GT", {1, 43}}, {"LT_LT", {1, 43}}, {"MINUS", {1, 43}}, {"P", {1, 43}}, {"PCT", {1, 43}}, {"PIPE", {1, 43}}, {"PLUS", {1, 43}}, {"SLASH", {1, 43}}, {"SLASH_SLASH", {1, 43}}, {"STAR", {1, 43}}, {"STAR_STAR", {1, 43}}, {"RPAREN", {1, 43}}, {"COMMA", {1, 43}}, {"EOF_", {1, 43}}},
	/* State 67 */ {{"PIPE", {1, 2}}, {"RPAREN", {1, 2}}, {"COMMA", {1, 2}}, {"EOF_", {1, 2}}},
	/* State 68 */ {{"PLUS", {0, 42}}, {"MINUS", {0, 43}}, {"AMP", {1, 13}}, {"CARET_PIPE", {1, 13}}, {"PIPE", {1, 13}}, {"LT_LT", {1, 13}}, {"GT_GT", {1, 13}}, {"RPAREN", {1, 13}}, {"COMMA", {1, 13}}, {"EOF_", {1, 13}}},
	/* State 69 */ {{"STAR", {0, 45}}, {"SLASH", {0, 46}}, {"SLASH_SLASH", {0, 47}}, {"PCT", {0, 48}}, {"C", {0, 49}}, {"P", {0, 50}}, {"AMP", {1, 16}}, {"CARET_PIPE", {1, 16}}, {"LT_LT", {1, 16}}, {"PIPE", {1, 16}}, {"GT_GT", {1, 16}}, {"PLUS", {1, 16}}, {"MINUS", {1, 16}}, {"RPAREN", {1, 16}}, {"COMMA", {1, 16}}, {"EOF_", {1, 16}}},
	/* State 70 */ {{"CARET", {0, 52}}, {"STAR_STAR", {0, 53}}, {"EXCL", {0, 54}}, {"AMP", {1, 19}}, {"CARET_PIPE", {1, 19}}, {"GT_GT", {1, 19}}, {"LT_LT", {1, 19}}, {"PIPE", {1, 19}}, {"PLUS", {1, 19}}, {"MINUS", {1, 19}}, {"STAR", {1, 19}}, {"SLASH", {1, 19}}, {"SLASH_SLASH", {1, 19}}, {"PCT", {1, 19}}, {"C", {1, 19}}, {"P", {1, 19}}, {"RPAREN", {1, 19}}, {"COMMA", {1, 19}}, {"EOF_", {1, 19}}},
	/* State 71 */ {{"AMP", {1, 26}}, {"CARET_PIPE", {1, 26}}, {"GT_GT", {1, 26}}, {"LT_LT", {1, 26}}, {"MINUS", {1, 26}}, {"PIPE", {1, 26}}, {"PLUS", {1, 26}}, {"STAR", {1, 26}}, {"SLASH", {1, 26}}, {"SLASH_SLASH", {1, 26}}, {"PCT", {1, 26}}, {"C", {1, 26}}, {"P", {1, 26}}, {"CARET", {1, 26}}, {"STAR_STAR", {1, 26}}, {"EXCL", {1, 26}}, {"RPAREN", {1, 26}}, {"COMMA", {1, 26}}, {"EOF_", {1, 26}}},
	/* State 72 */ {{"PIPE", {0, 73}}},
	/* State 73 */ {{"AMP", {1, 41}}, {"C", {1, 41}}, {"CARET", {1, 41}}, {"CARET_PIPE", {1, 41}}, {"EXCL", {1, 41}}, {"GT_GT", {1, 41}}, {"LT_LT", {1, 41}}, {"MINUS", {1, 41}}, {"P", {1, 41}}, {"PCT", {1, 41}}, {"PIPE", {1, 41}}, {"PLUS", {1, 41}}, {"SLASH", {1, 41}}, {"SLASH_SLASH", {1, 41}}, {"STAR", {1, 41}}, {"STAR_STAR", {1, 41}}, {"RPAREN", {1, 41}}, {"COMMA", {1, 41}}, {"EOF_", {1, 41}}},
	/* State 74 */ {{"CARET", {0, 52}}, {"STAR_STAR", {0, 53}}, {"EXCL", {0, 54}}, {"AMP", {1, 20}}, {"CARET_PIPE", {1, 20}}, {"GT_GT", {1, 20}}, {"LT_LT", {1, 20}}, {"PIPE", {1, 20}}, {"PLUS", {1, 20}}, {"MINUS", {1, 20}}, {"STAR", {1, 20}}, {"SLASH", {1, 20}}, {"SLASH_SLASH", {1, 20}}, {"PCT", {1, 20}}, {"C", {1, 20}}, {"P", {1, 20}}, {"RPAREN", {1, 20}}, {"COMMA", {1, 20}}, {"EOF_", {1, 20}}},
	/* State 75 */ {{"AMP", {1, 42}}, {"C", {1, 42}}, {"CARET", {1, 42}}, {"CARET_PIPE", {1, 42}}, {"EXCL", {1, 42}}, {"GT_GT", {1, 42}}, {"LT_LT", {1, 42}}, {"MINUS", {1, 42}}, {"P", {1, 42}}, {"PCT", {1, 42}}, {"PIPE", {1, 42}}, {"PLUS", {1, 42}}, {"SLASH", {1, 42}}, {"SLASH_SLASH", {1, 42}}, {"STAR", {1, 42}}, {"STAR_STAR", {1, 42}}, {"RPAREN", {1, 42}}, {"COMMA", {1, 42}}, {"EOF_", {1, 42}}},
	/* State 76 */ {{"CARET", {0, 52}}, {"STAR_STAR", {0, 53}}, {"EXCL", {0, 54}}, {"AMP", {1, 21}}, {"CARET_PIPE", {1, 21}}, {"GT_GT", {1, 21}}, {"LT_LT", {1, 21}}, {"PIPE", {1, 21}}, {"PLUS", {1, 21}}, {"MINUS", {1, 21}}, {"STAR", {1, 21}}, {"SLASH", {1, 21}}, {"SLASH_SLASH", {1, 21}}, {"PCT", {1, 21}}, {"C", {1, 21}}, {"P", {1, 21}}, {"RPAREN", {1, 21}}, {"COMMA", {1, 21}}, {"EOF_", {1, 21}}},
	/* State 77 */ {{"CARET", {0, 52}}, {"STAR_STAR", {0, 53}}, {"EXCL", {0, 54}}, {"AMP", {1, 22}}, {"CARET_PIPE", {1, 22}}, {"GT_GT", {1, 22}}, {"LT_LT", {1, 22}}, {"PIPE", {1, 22}}, {"PLUS", {1, 22}}, {"MINUS", {1, 22}}, {"STAR", {1, 22}}, {"SLASH", {1, 22}}, {"SLASH_SLASH", {1, 22}}, {"PCT", {1, 22}}, {"C", {1, 22}}, {"P", {1, 22}}, {"RPAREN", {1, 22}}, {"COMMA", {1, 22}}, {"EOF_", {1, 22}}},
	/* State 78 */ {{"CARET", {0, 52}}, {"STAR_STAR", {0, 53}}, {"EXCL", {0, 54}}, {"AMP", {1, 23}}, {"CARET_PIPE", {1, 23}}, {"GT_GT", {1, 23}}, {"LT_LT", {1, 23}}, {"PIPE", {1, 23}}, {"PLUS", {1, 23}}, {"MINUS", {1, 23}}, {"STAR", {1, 23}}, {"SLASH", {1, 23}}, {"SLASH_SLASH", {1, 23}}, {"PCT", {1, 23}}, {"C", {1, 23}}, {"P", {1, 23}}, {"RPAREN", {1, 23}}, {"COMMA", {1, 23}}, {"EOF_", {1, 23}}},
	/* State 79 */ {{"PIPE", {1, 3}}, {"RPAREN", {1, 3}}, {"COMMA", {1, 3}}, {"EOF_", {1, 3}}}
});