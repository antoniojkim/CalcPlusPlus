rules = """
statement expr
expr lvalue EQUALS expr1
expr lvalue COLON_EQUALS expr1
expr lvalue L_ARROW expr1
expr expr1
expr1 expr13
expr13 expr13 PIPE expr12
expr13 expr12
expr12 expr12 CARET_PIPE expr11
expr12 expr11
expr11 expr11 AMP expr7
expr11 expr7
expr7 expr7 LT_LT expr6
expr7 expr7 GT_GT expr6
expr7 expr6
expr6 expr6 PLUS expr5
expr6 expr6 MINUS expr5
expr6 expr5
expr5 expr5 STAR expr4
expr5 expr5 SLASH expr4
expr5 expr5 SLASH_SLASH expr4
expr5 expr5 PCT expr4
expr5 exprn exprn
expr5 expr4
expr4 expr4 CARET expr3
expr4 expr4 EXCL
expr4 expr3
expr3 TILDE exprn
expr3 exprn
exprn PIPE expr PIPE
exprn LPAREN expr RPAREN
exprn multiid LPAREN RPAREN
exprn multiid LPAREN arglist RPAREN
exprn multiid factor
exprn lvalue
multiid multiid ID
multiid
factor NUM
factor X
factor Y
factor NONE_
factor TRUE_
factor FALSE_
lvalue LPAREN lvalue RPAREN
arglist expr
arglist expr COMMA arglist
""".strip()

rules = [r.split() for r in rules.split("\n")]

# print("""{{
#     {}
# }}""".format(",\n    ".join("{{\"{0}\", generate_{1}_expression}}".format(" ".join(r), "_".join(r)) for r in rules)))

print("\n\n".join("""
expression generate_{0}_expression(NonTerminal* nonterminal){{
    throw Exception("{0} not implemented");
}}
""".strip().format("_".join(r)) for r in rules))