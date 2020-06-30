# -*- coding: utf-8 -*-
import os

from .Template import wrap, Template, expr_dir, func_dir


def generate_functions(args=None):
    headers = []
    function_decorators = []
    for header in os.listdir(os.path.join(func_dir, "Functions")):
        if header.endswith(".h"):
            headers.append(os.path.join("Functions", header))
            with open(os.path.join(func_dir, "Functions", header)) as file:
                for row in file:
                    if row.strip().startswith("// @Function"):
                        function_decorators.append(row.strip())

    operator_decorators = []
    for header in os.listdir(os.path.join(func_dir, "Operators")):
        if header.endswith(".h"):
            headers.append(os.path.join("Operators", header))
            with open(os.path.join(func_dir, "Operators", header)) as file:
                for row in file:
                    if row.strip().startswith("// @Operator"):
                        operator_decorators.append(row.strip())

    functions = []
    for decorator in function_decorators:
        decorator = decorator.split()
        functions.extend((name, decorator[2]) for name in decorator[2:])

    for decorator in operator_decorators:
        decorator = decorator.split()
        functions.extend((symbol, decorator[2]) for symbol in decorator[3:])

    headers.sort()
    functions.sort()

    with Template(
        "Functions.h", os.path.join(expr_dir, "..", "Functions", "Functions.h"),
    ) as template:
        template.replace(
            numFunctions=len(functions),
            names=wrap((f'"{name}"' for name, pointer in functions), indent="        "),
        )

    with Template(
        "Functions.cc", os.path.join(expr_dir, "..", "Functions", "Functions.cc"),
    ) as template:
        template.replace(
            includes=os.linesep.join(f'#include "{header}"' for header in headers),
            functions=wrap(
                (f"&Function::{pointer}" for name, pointer in functions), indent="    "
            ),
        )

    return functions


if __name__ == "__main__":
    generate_functions()
