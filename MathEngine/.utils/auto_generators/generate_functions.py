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
            template.replace(
                includes=os.linesep.join(
                    sorted(
                        f'#include "{os.path.join(dir, header)}"'
                        for dir in os.listdir(
                            os.path.join(expr_dir, "FunctionExpressions")
                        )
                        if os.path.isdir(
                            os.path.join(expr_dir, "FunctionExpressions", dir)
                        )
                        for header in os.listdir(
                            os.path.join(expr_dir, "FunctionExpressions", dir)
                        )
                        if header.endswith(".h")
                    )
                ),
                valueFunctions=wrap(
                    (
                        f"f_{name}" if not hasExpression(name) else "nullptr"
                        for name in functionNames
                    )
                ),
                exprFunctions=wrap(
                    (
                        f"fe_{name}" if hasExpression(name) else "nullptr"
                        for name in functionNames
                    )
                ),
                derivativeFunctions=wrap(
                    (
                        f"fprime_{name}" if hasDerivative(name) else "nullptr"
                        for name in functionNames
                    )
                ),
            )

    return locals()


if __name__ == "__main__":
    generate_functions()
