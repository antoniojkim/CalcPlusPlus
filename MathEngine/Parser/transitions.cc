
#include <algorithm>
#include <vector>

#include "transitions.h"

const std::array<std::string, numTerminals> terminalStrings = {
	"AMP", "APOSTROPHE", "BACKSLASH", "BACKTICK", "BOF_", "C", "CARET",
	"CARET_PIPE", "COLON", "COLON_EQUALS", "COMMA", "DOLLAR", "DOT", "EOF_",
	"EQUALS", "EXCL", "FALSE_", "GT_GT", "HEX", "ID", "LBRACE", "LPAREN", "LSQUARE",
	"LT_LT", "L_ARROW", "MINUS", "NONE_", "NULL_", "NUM", "P", "PCT", "PIPE",
	"PLUS", "POUND", "QUESTION", "QUOTE", "RBRACE", "RPAREN", "RSQUARE", "R_ARROW",
	"SEMICOLON", "SLASH", "SLASH_SLASH", "STAR", "STAR_STAR", "STR", "TILDE",
	"TRUE_", "UNDERSCORE", "X", "Y"
};

const std::array<std::string, numNonTerminals> nonterminalStrings = {
	"start", "arglist", "expr", "expr1", "expr11", "expr12", "expr13", "expr3",
	"expr4", "expr5", "expr6", "expr7", "exprn", "factor", "lvalue", "statement"
};

std::string getTerminalString(Terminal terminal){ return terminalStrings[terminal]; }
std::string getNonTerminalString(NonTerminal nonterminal){ return nonterminalStrings[nonterminal + numNonTerminals]; }

int convertTokenType(Scanner::Type type){
	const std::string typeString = Scanner::typeStrings[type];
    auto first = terminalStrings.data();
    auto last = first + numTerminals;
	auto it = std::lower_bound(first, last, typeString);
	if (it != last && !(typeString < *it)){
		return it - first;
	}
	throw "Cannot find " + typeString + " in Terminals";
}

const std::array<std::array<int, maxRuleLength>, numRules> rules = {{
	{2, statement, expr, -1, -1, -1},
	{4, expr, lvalue, EQUALS, expr1, -1},
	{4, expr, lvalue, COLON_EQUALS, expr1, -1},
	{4, expr, lvalue, L_ARROW, expr1, -1},
	{2, expr, expr1, -1, -1, -1},
	{2, expr1, expr13, -1, -1, -1},
	{4, expr13, expr13, PIPE, expr12, -1},
	{2, expr13, expr12, -1, -1, -1},
	{4, expr12, expr12, CARET_PIPE, expr11, -1},
	{2, expr12, expr11, -1, -1, -1},
	{4, expr11, expr11, AMP, expr7, -1},
	{2, expr11, expr7, -1, -1, -1},
	{4, expr7, expr7, LT_LT, expr6, -1},
	{4, expr7, expr7, GT_GT, expr6, -1},
	{2, expr7, expr6, -1, -1, -1},
	{4, expr6, expr6, PLUS, expr5, -1},
	{4, expr6, expr6, MINUS, expr5, -1},
	{2, expr6, expr5, -1, -1, -1},
	{4, expr5, expr5, STAR, expr4, -1},
	{4, expr5, expr5, SLASH, expr4, -1},
	{4, expr5, expr5, SLASH_SLASH, expr4, -1},
	{4, expr5, expr5, PCT, expr4, -1},
	{4, expr5, expr5, C, expr4, -1},
	{4, expr5, expr5, P, expr4, -1},
	{2, expr5, expr4, -1, -1, -1},
	{4, expr4, expr4, CARET, expr3, -1},
	{4, expr4, expr4, STAR_STAR, expr3, -1},
	{3, expr4, expr4, EXCL, -1, -1},
	{2, expr4, expr3, -1, -1, -1},
	{3, expr3, TILDE, exprn, -1, -1},
	{2, expr3, exprn, -1, -1, -1},
	{3, exprn, ID, exprn, -1, -1},
	{5, exprn, ID, LPAREN, arglist, RPAREN},
	{2, exprn, factor, -1, -1, -1},
	{2, exprn, lvalue, -1, -1, -1},
	{2, factor, NUM, -1, -1, -1},
	{2, factor, X, -1, -1, -1},
	{2, factor, Y, -1, -1, -1},
	{2, factor, NONE_, -1, -1, -1},
	{2, factor, TRUE_, -1, -1, -1},
	{2, factor, FALSE_, -1, -1, -1},
	{4, factor, PIPE, expr, PIPE, -1},
	{4, factor, LPAREN, expr, RPAREN, -1},
	{4, lvalue, LPAREN, lvalue, RPAREN, -1},
	{1, arglist, -1, -1, -1, -1},
	{2, arglist, expr, -1, -1, -1},
	{4, arglist, expr, COMMA, arglist, -1},
	{4, start, BOF_, statement, EOF_, -1}
}};

const std::vector<std::map<int, int>> transitions = {
	/* State 0 */ {{{BOF_, -2}}},
	/* State 1 */ {{{statement, -3}, {expr, -4}, {lvalue, -5}, {expr1, -6}, {LPAREN, -7}, {expr13, -8}, {expr12, -9}, {expr11, -10}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}}},
	/* State 2 */ {{{EOF_, -27}}},
	/* State 3 */ {{{EOF_, 0}}},
	/* State 4 */ {{{EQUALS, -28}, {COLON_EQUALS, -29}, {L_ARROW, -30}, {AMP, 34}, {C, 34}, {CARET, 34}, {CARET_PIPE, 34}, {EXCL, 34}, {GT_GT, 34}, {LT_LT, 34}, {MINUS, 34}, {P, 34}, {PCT, 34}, {PIPE, 34}, {PLUS, 34}, {SLASH, 34}, {SLASH_SLASH, 34}, {STAR, 34}, {STAR_STAR, 34}, {RPAREN, 34}, {COMMA, 34}, {EOF_, 34}}},
	/* State 5 */ {{{PIPE, 4}, {RPAREN, 4}, {COMMA, 4}, {EOF_, 4}}},
	/* State 6 */ {{{lvalue, -65}, {expr, -66}, {LPAREN, -7}, {expr1, -6}, {expr13, -8}, {expr12, -9}, {expr11, -10}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}}},
	/* State 7 */ {{{PIPE, 5}, {RPAREN, 5}, {COMMA, 5}, {EOF_, 5}}},
	/* State 8 */ {{{CARET_PIPE, -36}, {PIPE, 7}, {RPAREN, 7}, {COMMA, 7}, {EOF_, 7}}},
	/* State 9 */ {{{AMP, -38}, {PIPE, 9}, {CARET_PIPE, 9}, {RPAREN, 9}, {COMMA, 9}, {EOF_, 9}}},
	/* State 10 */ {{{LT_LT, -40}, {GT_GT, -41}, {CARET_PIPE, 11}, {PIPE, 11}, {AMP, 11}, {RPAREN, 11}, {COMMA, 11}, {EOF_, 11}}},
	/* State 11 */ {{{PLUS, -43}, {MINUS, -44}, {AMP, 14}, {CARET_PIPE, 14}, {PIPE, 14}, {LT_LT, 14}, {GT_GT, 14}, {RPAREN, 14}, {COMMA, 14}, {EOF_, 14}}},
	/* State 12 */ {{{STAR, -46}, {SLASH, -47}, {SLASH_SLASH, -48}, {PCT, -49}, {C, -50}, {P, -51}, {AMP, 17}, {CARET_PIPE, 17}, {LT_LT, 17}, {PIPE, 17}, {GT_GT, 17}, {PLUS, 17}, {MINUS, 17}, {RPAREN, 17}, {COMMA, 17}, {EOF_, 17}}},
	/* State 13 */ {{{CARET, -53}, {STAR_STAR, -54}, {EXCL, -55}, {AMP, 24}, {CARET_PIPE, 24}, {GT_GT, 24}, {LT_LT, 24}, {PIPE, 24}, {PLUS, 24}, {MINUS, 24}, {STAR, 24}, {SLASH, 24}, {SLASH_SLASH, 24}, {PCT, 24}, {C, 24}, {P, 24}, {RPAREN, 24}, {COMMA, 24}, {EOF_, 24}}},
	/* State 14 */ {{{AMP, 28}, {CARET_PIPE, 28}, {GT_GT, 28}, {LT_LT, 28}, {MINUS, 28}, {PIPE, 28}, {PLUS, 28}, {STAR, 28}, {SLASH, 28}, {SLASH_SLASH, 28}, {PCT, 28}, {C, 28}, {P, 28}, {CARET, 28}, {STAR_STAR, 28}, {EXCL, 28}, {RPAREN, 28}, {COMMA, 28}, {EOF_, 28}}},
	/* State 15 */ {{{exprn, -57}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 16 */ {{{AMP, 30}, {C, 30}, {CARET, 30}, {CARET_PIPE, 30}, {GT_GT, 30}, {LT_LT, 30}, {MINUS, 30}, {P, 30}, {PCT, 30}, {PIPE, 30}, {PLUS, 30}, {SLASH, 30}, {SLASH_SLASH, 30}, {STAR, 30}, {STAR_STAR, 30}, {EXCL, 30}, {RPAREN, 30}, {COMMA, 30}, {EOF_, 30}}},
	/* State 17 */ {{{exprn, -58}, {LPAREN, -59}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}}},
	/* State 18 */ {{{AMP, 33}, {C, 33}, {CARET, 33}, {CARET_PIPE, 33}, {EXCL, 33}, {GT_GT, 33}, {LT_LT, 33}, {MINUS, 33}, {P, 33}, {PCT, 33}, {PIPE, 33}, {PLUS, 33}, {SLASH, 33}, {SLASH_SLASH, 33}, {STAR, 33}, {STAR_STAR, 33}, {RPAREN, 33}, {COMMA, 33}, {EOF_, 33}}},
	/* State 19 */ {{{AMP, 35}, {C, 35}, {CARET, 35}, {CARET_PIPE, 35}, {EXCL, 35}, {GT_GT, 35}, {LT_LT, 35}, {MINUS, 35}, {P, 35}, {PCT, 35}, {PIPE, 35}, {PLUS, 35}, {SLASH, 35}, {SLASH_SLASH, 35}, {STAR, 35}, {STAR_STAR, 35}, {RPAREN, 35}, {COMMA, 35}, {EOF_, 35}}},
	/* State 20 */ {{{AMP, 36}, {C, 36}, {CARET, 36}, {CARET_PIPE, 36}, {EXCL, 36}, {GT_GT, 36}, {LT_LT, 36}, {MINUS, 36}, {P, 36}, {PCT, 36}, {PIPE, 36}, {PLUS, 36}, {SLASH, 36}, {SLASH_SLASH, 36}, {STAR, 36}, {STAR_STAR, 36}, {RPAREN, 36}, {COMMA, 36}, {EOF_, 36}}},
	/* State 21 */ {{{AMP, 37}, {C, 37}, {CARET, 37}, {CARET_PIPE, 37}, {EXCL, 37}, {GT_GT, 37}, {LT_LT, 37}, {MINUS, 37}, {P, 37}, {PCT, 37}, {PIPE, 37}, {PLUS, 37}, {SLASH, 37}, {SLASH_SLASH, 37}, {STAR, 37}, {STAR_STAR, 37}, {RPAREN, 37}, {COMMA, 37}, {EOF_, 37}}},
	/* State 22 */ {{{AMP, 38}, {C, 38}, {CARET, 38}, {CARET_PIPE, 38}, {EXCL, 38}, {GT_GT, 38}, {LT_LT, 38}, {MINUS, 38}, {P, 38}, {PCT, 38}, {PIPE, 38}, {PLUS, 38}, {SLASH, 38}, {SLASH_SLASH, 38}, {STAR, 38}, {STAR_STAR, 38}, {RPAREN, 38}, {COMMA, 38}, {EOF_, 38}}},
	/* State 23 */ {{{AMP, 39}, {C, 39}, {CARET, 39}, {CARET_PIPE, 39}, {EXCL, 39}, {GT_GT, 39}, {LT_LT, 39}, {MINUS, 39}, {P, 39}, {PCT, 39}, {PIPE, 39}, {PLUS, 39}, {SLASH, 39}, {SLASH_SLASH, 39}, {STAR, 39}, {STAR_STAR, 39}, {RPAREN, 39}, {COMMA, 39}, {EOF_, 39}}},
	/* State 24 */ {{{AMP, 40}, {C, 40}, {CARET, 40}, {CARET_PIPE, 40}, {EXCL, 40}, {GT_GT, 40}, {LT_LT, 40}, {MINUS, 40}, {P, 40}, {PCT, 40}, {PIPE, 40}, {PLUS, 40}, {SLASH, 40}, {SLASH_SLASH, 40}, {STAR, 40}, {STAR_STAR, 40}, {RPAREN, 40}, {COMMA, 40}, {EOF_, 40}}},
	/* State 25 */ {{{expr, -73}, {lvalue, -5}, {expr1, -6}, {LPAREN, -7}, {expr13, -8}, {expr12, -9}, {expr11, -10}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}}},
	/* State 26 */ {{}},
	/* State 27 */ {{{expr1, -31}, {expr13, -8}, {expr12, -9}, {expr11, -10}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 28 */ {{{expr1, -68}, {expr13, -8}, {expr12, -9}, {expr11, -10}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 29 */ {{{expr1, -80}, {expr13, -8}, {expr12, -9}, {expr11, -10}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 30 */ {{{PIPE, 1}, {RPAREN, 1}, {COMMA, 1}, {EOF_, 1}}},
	/* State 31 */ {{{AMP, 34}, {C, 34}, {CARET, 34}, {CARET_PIPE, 34}, {EXCL, 34}, {GT_GT, 34}, {LT_LT, 34}, {MINUS, 34}, {P, 34}, {PCT, 34}, {PIPE, 34}, {PLUS, 34}, {SLASH, 34}, {SLASH_SLASH, 34}, {STAR, 34}, {STAR_STAR, 34}, {RPAREN, 34}, {COMMA, 34}, {EOF_, 34}}},
	/* State 32 */ {{{expr, -66}, {lvalue, -5}, {expr1, -6}, {LPAREN, -7}, {expr13, -8}, {expr12, -9}, {expr11, -10}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}}},
	/* State 33 */ {{{expr12, -35}, {expr11, -10}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 34 */ {{{CARET_PIPE, -36}, {PIPE, 6}, {RPAREN, 6}, {COMMA, 6}, {EOF_, 6}}},
	/* State 35 */ {{{expr11, -37}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 36 */ {{{AMP, -38}, {PIPE, 8}, {CARET_PIPE, 8}, {RPAREN, 8}, {COMMA, 8}, {EOF_, 8}}},
	/* State 37 */ {{{expr7, -39}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 38 */ {{{LT_LT, -40}, {GT_GT, -41}, {CARET_PIPE, 10}, {PIPE, 10}, {AMP, 10}, {RPAREN, 10}, {COMMA, 10}, {EOF_, 10}}},
	/* State 39 */ {{{expr6, -42}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 40 */ {{{expr6, -69}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 41 */ {{{PLUS, -43}, {MINUS, -44}, {AMP, 12}, {CARET_PIPE, 12}, {PIPE, 12}, {LT_LT, 12}, {GT_GT, 12}, {RPAREN, 12}, {COMMA, 12}, {EOF_, 12}}},
	/* State 42 */ {{{expr5, -45}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 43 */ {{{expr5, -70}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 44 */ {{{STAR, -46}, {SLASH, -47}, {SLASH_SLASH, -48}, {PCT, -49}, {C, -50}, {P, -51}, {AMP, 15}, {CARET_PIPE, 15}, {LT_LT, 15}, {PIPE, 15}, {GT_GT, 15}, {PLUS, 15}, {MINUS, 15}, {RPAREN, 15}, {COMMA, 15}, {EOF_, 15}}},
	/* State 45 */ {{{expr4, -52}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 46 */ {{{expr4, -71}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 47 */ {{{expr4, -75}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 48 */ {{{expr4, -77}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 49 */ {{{expr4, -78}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 50 */ {{{expr4, -79}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 51 */ {{{CARET, -53}, {STAR_STAR, -54}, {EXCL, -55}, {AMP, 18}, {CARET_PIPE, 18}, {GT_GT, 18}, {LT_LT, 18}, {PIPE, 18}, {PLUS, 18}, {MINUS, 18}, {STAR, 18}, {SLASH, 18}, {SLASH_SLASH, 18}, {PCT, 18}, {C, 18}, {P, 18}, {RPAREN, 18}, {COMMA, 18}, {EOF_, 18}}},
	/* State 52 */ {{{expr3, -56}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 53 */ {{{expr3, -72}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {lvalue, -32}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {LPAREN, -33}}},
	/* State 54 */ {{{AMP, 27}, {CARET_PIPE, 27}, {GT_GT, 27}, {LT_LT, 27}, {MINUS, 27}, {PIPE, 27}, {PLUS, 27}, {STAR, 27}, {SLASH, 27}, {SLASH_SLASH, 27}, {PCT, 27}, {C, 27}, {P, 27}, {CARET, 27}, {STAR_STAR, 27}, {EXCL, 27}, {RPAREN, 27}, {COMMA, 27}, {EOF_, 27}}},
	/* State 55 */ {{{AMP, 25}, {CARET_PIPE, 25}, {GT_GT, 25}, {LT_LT, 25}, {MINUS, 25}, {PIPE, 25}, {PLUS, 25}, {STAR, 25}, {SLASH, 25}, {SLASH_SLASH, 25}, {PCT, 25}, {C, 25}, {P, 25}, {CARET, 25}, {STAR_STAR, 25}, {EXCL, 25}, {RPAREN, 25}, {COMMA, 25}, {EOF_, 25}}},
	/* State 56 */ {{{AMP, 29}, {C, 29}, {CARET, 29}, {CARET_PIPE, 29}, {GT_GT, 29}, {LT_LT, 29}, {MINUS, 29}, {P, 29}, {PCT, 29}, {PIPE, 29}, {PLUS, 29}, {SLASH, 29}, {SLASH_SLASH, 29}, {STAR, 29}, {STAR_STAR, 29}, {EXCL, 29}, {RPAREN, 29}, {COMMA, 29}, {EOF_, 29}}},
	/* State 57 */ {{{AMP, 31}, {C, 31}, {CARET, 31}, {CARET_PIPE, 31}, {EXCL, 31}, {GT_GT, 31}, {LT_LT, 31}, {MINUS, 31}, {P, 31}, {PCT, 31}, {PIPE, 31}, {PLUS, 31}, {SLASH, 31}, {SLASH_SLASH, 31}, {STAR, 31}, {STAR_STAR, 31}, {RPAREN, 31}, {COMMA, 31}, {EOF_, 31}}},
	/* State 58 */ {{{arglist, -60}, {expr, -61}, {lvalue, -5}, {expr1, -6}, {LPAREN, -7}, {expr13, -8}, {expr12, -9}, {expr11, -10}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {RPAREN, 44}}},
	/* State 59 */ {{{RPAREN, -62}}},
	/* State 60 */ {{{COMMA, -63}, {RPAREN, 45}}},
	/* State 61 */ {{{AMP, 32}, {C, 32}, {CARET, 32}, {CARET_PIPE, 32}, {EXCL, 32}, {GT_GT, 32}, {LT_LT, 32}, {MINUS, 32}, {P, 32}, {PCT, 32}, {PIPE, 32}, {PLUS, 32}, {SLASH, 32}, {SLASH_SLASH, 32}, {STAR, 32}, {STAR_STAR, 32}, {RPAREN, 32}, {COMMA, 32}, {EOF_, 32}}},
	/* State 62 */ {{{arglist, -64}, {expr, -61}, {lvalue, -5}, {expr1, -6}, {LPAREN, -7}, {expr13, -8}, {expr12, -9}, {expr11, -10}, {expr7, -11}, {expr6, -12}, {expr5, -13}, {expr4, -14}, {expr3, -15}, {TILDE, -16}, {exprn, -17}, {ID, -18}, {factor, -19}, {NUM, -20}, {X, -21}, {Y, -22}, {NONE_, -23}, {TRUE_, -24}, {FALSE_, -25}, {PIPE, -26}, {RPAREN, 44}}},
	/* State 63 */ {{{RPAREN, 46}}},
	/* State 64 */ {{{RPAREN, -67}, {COLON_EQUALS, -29}, {L_ARROW, -30}}},
	/* State 65 */ {{{RPAREN, -76}}},
	/* State 66 */ {{{EQUALS, 43}, {COLON_EQUALS, 43}, {L_ARROW, 43}, {AMP, 43}, {C, 43}, {CARET, 43}, {CARET_PIPE, 43}, {EXCL, 43}, {GT_GT, 43}, {LT_LT, 43}, {MINUS, 43}, {P, 43}, {PCT, 43}, {PIPE, 43}, {PLUS, 43}, {SLASH, 43}, {SLASH_SLASH, 43}, {STAR, 43}, {STAR_STAR, 43}, {RPAREN, 43}, {COMMA, 43}, {EOF_, 43}}},
	/* State 67 */ {{{PIPE, 2}, {RPAREN, 2}, {COMMA, 2}, {EOF_, 2}}},
	/* State 68 */ {{{PLUS, -43}, {MINUS, -44}, {AMP, 13}, {CARET_PIPE, 13}, {PIPE, 13}, {LT_LT, 13}, {GT_GT, 13}, {RPAREN, 13}, {COMMA, 13}, {EOF_, 13}}},
	/* State 69 */ {{{STAR, -46}, {SLASH, -47}, {SLASH_SLASH, -48}, {PCT, -49}, {C, -50}, {P, -51}, {AMP, 16}, {CARET_PIPE, 16}, {LT_LT, 16}, {PIPE, 16}, {GT_GT, 16}, {PLUS, 16}, {MINUS, 16}, {RPAREN, 16}, {COMMA, 16}, {EOF_, 16}}},
	/* State 70 */ {{{CARET, -53}, {STAR_STAR, -54}, {EXCL, -55}, {AMP, 19}, {CARET_PIPE, 19}, {GT_GT, 19}, {LT_LT, 19}, {PIPE, 19}, {PLUS, 19}, {MINUS, 19}, {STAR, 19}, {SLASH, 19}, {SLASH_SLASH, 19}, {PCT, 19}, {C, 19}, {P, 19}, {RPAREN, 19}, {COMMA, 19}, {EOF_, 19}}},
	/* State 71 */ {{{AMP, 26}, {CARET_PIPE, 26}, {GT_GT, 26}, {LT_LT, 26}, {MINUS, 26}, {PIPE, 26}, {PLUS, 26}, {STAR, 26}, {SLASH, 26}, {SLASH_SLASH, 26}, {PCT, 26}, {C, 26}, {P, 26}, {CARET, 26}, {STAR_STAR, 26}, {EXCL, 26}, {RPAREN, 26}, {COMMA, 26}, {EOF_, 26}}},
	/* State 72 */ {{{PIPE, -74}}},
	/* State 73 */ {{{AMP, 41}, {C, 41}, {CARET, 41}, {CARET_PIPE, 41}, {EXCL, 41}, {GT_GT, 41}, {LT_LT, 41}, {MINUS, 41}, {P, 41}, {PCT, 41}, {PIPE, 41}, {PLUS, 41}, {SLASH, 41}, {SLASH_SLASH, 41}, {STAR, 41}, {STAR_STAR, 41}, {RPAREN, 41}, {COMMA, 41}, {EOF_, 41}}},
	/* State 74 */ {{{CARET, -53}, {STAR_STAR, -54}, {EXCL, -55}, {AMP, 20}, {CARET_PIPE, 20}, {GT_GT, 20}, {LT_LT, 20}, {PIPE, 20}, {PLUS, 20}, {MINUS, 20}, {STAR, 20}, {SLASH, 20}, {SLASH_SLASH, 20}, {PCT, 20}, {C, 20}, {P, 20}, {RPAREN, 20}, {COMMA, 20}, {EOF_, 20}}},
	/* State 75 */ {{{AMP, 42}, {C, 42}, {CARET, 42}, {CARET_PIPE, 42}, {EXCL, 42}, {GT_GT, 42}, {LT_LT, 42}, {MINUS, 42}, {P, 42}, {PCT, 42}, {PIPE, 42}, {PLUS, 42}, {SLASH, 42}, {SLASH_SLASH, 42}, {STAR, 42}, {STAR_STAR, 42}, {RPAREN, 42}, {COMMA, 42}, {EOF_, 42}}},
	/* State 76 */ {{{CARET, -53}, {STAR_STAR, -54}, {EXCL, -55}, {AMP, 21}, {CARET_PIPE, 21}, {GT_GT, 21}, {LT_LT, 21}, {PIPE, 21}, {PLUS, 21}, {MINUS, 21}, {STAR, 21}, {SLASH, 21}, {SLASH_SLASH, 21}, {PCT, 21}, {C, 21}, {P, 21}, {RPAREN, 21}, {COMMA, 21}, {EOF_, 21}}},
	/* State 77 */ {{{CARET, -53}, {STAR_STAR, -54}, {EXCL, -55}, {AMP, 22}, {CARET_PIPE, 22}, {GT_GT, 22}, {LT_LT, 22}, {PIPE, 22}, {PLUS, 22}, {MINUS, 22}, {STAR, 22}, {SLASH, 22}, {SLASH_SLASH, 22}, {PCT, 22}, {C, 22}, {P, 22}, {RPAREN, 22}, {COMMA, 22}, {EOF_, 22}}},
	/* State 78 */ {{{CARET, -53}, {STAR_STAR, -54}, {EXCL, -55}, {AMP, 23}, {CARET_PIPE, 23}, {GT_GT, 23}, {LT_LT, 23}, {PIPE, 23}, {PLUS, 23}, {MINUS, 23}, {STAR, 23}, {SLASH, 23}, {SLASH_SLASH, 23}, {PCT, 23}, {C, 23}, {P, 23}, {RPAREN, 23}, {COMMA, 23}, {EOF_, 23}}},
	/* State 79 */ {{{PIPE, 3}, {RPAREN, 3}, {COMMA, 3}, {EOF_, 3}}}
};