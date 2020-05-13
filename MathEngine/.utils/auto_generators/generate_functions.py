# -*- coding: utf-8 -*-
import os

from .Template import wrap, Specifications, Template, expr_dir


def generate_functions(args=None):
    with Specifications("functions.yml") as specs:
        functionNames = sorted(list(specs["functions"].keys()))
        functions = {
            name: val if val is not None else {}
            for name, val in specs["functions"].items()
        }

        def nargs(name):
            return functions[name].get("nargs", 1)

        def hasExpression(name):
            return "expression" in functions[name]

        def hasDerivative(name):
            return "derivative" in functions[name]

        with Template(
            "Functions.h", os.path.join(expr_dir, "FunctionExpressions", "Functions.h"),
        ) as template:
            template.verify(specs)
            template.replace(
                numFunctions=len(functions),
                functionNames=wrap(
                    (f'"{name}"' for name in functionNames), indent="        "
                ),
                functionNameLengths=wrap(
                    map(str, (len(name) for name in functionNames)), indent="        "
                ),
                functionOrderByLength=wrap(
                    (
                        str(i)
                        for i, f in sorted(
                            list(enumerate(functionNames)),
                            key=lambda k: len(k[1]),
                            reverse=True,
                        )
                    ),
                    indent="        ",
                ),
                functionNumArgs=wrap(
                    (str(functions[name].get("nargs", 1)) for name in functionNames),
                    indent="        ",
                ),
            )

        with Template(
            "FunctionDirectory.cc",
            os.path.join(expr_dir, "FunctionExpressions", "FunctionDirectory.cc"),
        ) as template:
            template.verify(specs)
            template.replace(
                unaryFunctions=wrap(
                    (
                        f"f_{name}"
                        if nargs(name) == 1 and not hasExpression(name)
                        else "nullptr"
                        for name in functionNames
                    )
                ),
                unaryFunctionExprs=wrap(
                    (
                        f"fe_{name}"
                        if hasExpression(name) and nargs(name) == 1
                        else "nullptr"
                        for name in functionNames
                    )
                ),
                unaryFunctionDerivatives=wrap(
                    (
                        f"fprime_{name}"
                        if hasDerivative(name) and nargs(name) == 1
                        else "nullptr"
                        for name in functionNames
                    )
                ),
            )
            template.replace(
                multiFunctions=wrap(
                    (
                        f"f_{name}"
                        if not hasExpression(name) and not (0 <= nargs(name) <= 1)
                        else "nullptr"
                        for name in functionNames
                    )
                ),
                multiFunctionExprs=wrap(
                    (
                        f"fe_{name}"
                        if hasExpression(name) and not (0 <= nargs(name) <= 1)
                        else "nullptr"
                        for name in functionNames
                    )
                ),
            )

    return locals()


if __name__ == "__main__":
    generate_functions()
