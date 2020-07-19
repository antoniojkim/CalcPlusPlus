# -*- coding: utf-8 -*-
import os
import re

from .Template import wrap, Template, func_dir


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


def generate_functions(args=None):
    function_files = (
        (subdir, file)
        for subdir in ("Functions", "Operators")
        for file in os.listdir(os.path.join(func_dir, subdir))
        if file.endswith(".cc")
    )

    functions = []
    for subdir, function_file in function_files:
        with open(os.path.join(func_dir, subdir, function_file)) as file:
            contents = file.read()
            for dectype, decorator in decorators.items():
                index = 0
                while True:
                    match = decorator.search(contents, index)
                    if not match:
                        break

                    functions.append(
                        {
                            "name": match.group("name").strip(),
                            "aliases": match.group("aliases"),
                            "type": dectype,
                        }
                    )
                    index = match.end()

    def get_all():
        for function in functions:
            yield function["name"], function["name"], False
            if function["aliases"] is not None:
                isOperator = "true" if function["type"] == "operator" else "false"
                for alias in function["aliases"].split():
                    if len(alias.strip()) > 0:
                        yield alias.strip(), function["name"], isOperator

    all_names, all_refs, all_operators = zip(*sorted(get_all()))

    declarations = sorted(
        f"DECLARE_FUNCTION_EXPRESSION({name});" for name in set(all_refs)
    )
    function_constructors = [f"make_fe_{name}" for name in all_refs]

    with Template("Functions.h", os.path.join(func_dir, "Functions.h")) as template:
        template.replace(
            numFunctions=len(all_names),
            names=wrap(map('"{}"'.format, all_names), indent="\t\t"),
            declarations="\n\t".join(declarations),
        )

    with Template("Functions.cc", os.path.join(func_dir, "Functions.cc")) as template:
        template.replace(
            FunctionConstructors=wrap(", ".join(function_constructors), indent="\t\t"),
            FunctionIsOperator=wrap(", ".join(all_operators), indent="\t\t"),
        )


if __name__ == "__main__":
    generate_functions()
