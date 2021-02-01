# -*- coding: utf-8 -*-
import os
import re

from sourcegen import SourceGenerator

math_functions = {
    # unary functions
    "sin",
    "cos",
    "tan",
    "sec",
    "csc",
    "cot",
    "arcsin",
    "arccos",
    "arctan",
    "arcsec",
    "arccsc",
    "arccot",
    "exp",
    "exp2",
    "expm1",
    "ln",
    "log",
    "sigmoid",
    "sqrt",
    "cbrt",
    "cb",
    "sqr",
    # operators
    "add",
    "subtract",
    "multiply",
    "divide",
    "modulo",
    "exponent",
}

decorators = {
    "function": re.compile(
        r"// @Function {name}{aliases}".format(
            name=r"(?P<name>{id})", aliases=r"(:(?P<aliases>( *{id})+))?",
        ).format(id=r"[a-zA-Z_][a-zA-Z0-9_]*",)
    ),
    "operator": re.compile(
        r"// @Operator {name}{aliases}".format(
            name=r"(?P<name>[a-zA-Z_][a-zA-Z0-9_]*)",
            aliases=r"(:(?P<aliases>( *\S+)+))?",
        )
    ),
}


def extract_functions(filepath):
    functions = {dectype: [] for dectype in decorators.keys()}

    with open(filepath) as file:
        contents = file.read()
        for dectype, decorator in decorators.items():
            index = 0
            while True:
                match = decorator.search(contents, index)
                if not match:
                    break

                function = {
                    "name": match.group("name").strip(),
                    "aliases": match.group("aliases"),
                }
                if function["aliases"] is not None:
                    function["aliases"] = function["aliases"].split()
                else:
                    del function["aliases"]

                functions[dectype].append(function)

                index = match.end()

    return functions


template = "const expression {0} = std::shared_ptr<fexpr::{0}>(new fexpr::{0}());"

if __name__ == "__main__":
    function_files = sorted(
        os.path.join(subdir, file)
        for subdir in ("Functions", "Operators")
        for file in os.listdir(subdir)
        if file.endswith(".cc")
    )

    functions = {dectype: [] for dectype in decorators.keys()}

    for filepath in function_files:
        fs = extract_functions(filepath)

        if len(fs["function"]) > 0:
            for dectype in decorators.keys():
                functions[dectype].extend(fs[dectype])

            with SourceGenerator(filepath) as source:
                print(filepath)
                source["functions"].set_text(
                    map(template.format, sorted(f["name"] for f in fs["function"]),),
                    delimiter="\n",
                )

    with SourceGenerator("../Expressions/ExpressionFunctions.h") as source:
        source["functions"].set_text(
            map(
                "expression {}(expression);".format,
                sorted(
                    f["name"]
                    for f in functions["function"]
                    if f["name"] in math_functions
                ),
            ),
            delimiter="\n",
        )

    with SourceGenerator("Functions.h") as source:
        source["functions"].set_text(
            map(
                "extern const expression {};".format,
                sorted(f["name"] for f in functions["function"]),
            ),
            delimiter="\n",
        )

    functionAliases = sorted(
        (alias, f["name"])
        for f in functions["function"]
        for alias in [f["name"]] + f.get("aliases", [])
    )

    with SourceGenerator("Functions.cc") as source:
        source["numFunctions"].set_text(len(functionAliases))
        source["functionNames"].set_text(
            (alias for alias, name in functionAliases),
            delimiter=", ",
            quote='"',
            wrap_width=80,
        )
        source["functionExprs"].set_text(
            (name for alias, name in functionAliases), delimiter=", ", wrap_width=80,
        )
