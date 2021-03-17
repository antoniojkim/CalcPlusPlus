# -*- coding: utf-8 -*-
import os
import re
import yaml

try:
    from yaml import CLoader as Loader
except ImportError:
    from yaml import Loader


from sourcegen import SourceGenerator

decorator = re.compile(
    r"// @Operator {name}{kind}".format(
        name=r"(?P<name>[a-zA-Z_][a-zA-Z0-9_]*)",
        kind=r":(?P<kind>( *[a-zA-Z_][a-zA-Z0-9_]*)+)",
    )
)


def extract_operators(filepath):
    operators = []

    with open(filepath) as file:
        contents = file.read()
        index = 0
        while True:
            match = decorator.search(contents, index)
            if not match:
                break

            operators.append(
                {
                    "name": match.group("name").strip(),
                    "kinds": match.group("kind").strip().split(),
                }
            )
            index = match.end()

    return operators


template = "const expression {0} = std::shared_ptr<opexpr::{0}>(new opexpr::{0}());"

if __name__ == "__main__":

    with open("../symbols.yml") as file:
        symbols = yaml.load(file, Loader)
        operators = symbols["operators"]

    def isRightAssociative(metadata):
        if metadata is not None and "rightAssociative" in metadata:
            return 1
        return -1

    def isSingleOperator(metadata):
        if metadata is not None and "singleOperator" in metadata:
            return 1
        return 0

    opinfo = [
        (
            operator,
            ((i + 1) * isRightAssociative(metadata), isSingleOperator(metadata),),
        )
        for i, group in enumerate(operators)
        for operator, metadata in group.items()
    ]
    opinfo.sort()

    operator_files = sorted(
        os.path.join("Operators", file)
        for file in os.listdir("Operators")
        if file.endswith(".cc")
    )

    op_decorators = []

    for filepath in operator_files:
        ops = extract_operators(filepath)

        if len(ops) > 0:
            op_decorators.extend(ops)

            with SourceGenerator(filepath) as source:
                source["operators"].set_text(
                    map(template.format, sorted(op["name"] for op in ops)),
                    delimiter="\n",
                )

    with SourceGenerator("Operators.h") as source:
        source["operators"].set_text(
            map(
                "extern const expression {};".format,
                sorted(op["name"] for op in op_decorators),
            ),
            delimiter="\n",
        )

    with SourceGenerator("Operators.cc") as source:
        source["size"].set_text(len(opinfo))
        source["offset"].set_text(len(symbols["tokens"]))

        source["precedences"].set_text(
            (str(p) for op, (p, s) in opinfo), delimiter=", ", wrap_width=80
        )
        source["single"].set_text(
            (str(s) for op, (p, s) in opinfo), delimiter=", ", wrap_width=80
        )
        source["operator_cases"].set_text(
            (
                f"case Token::Kind::{kind}: return calcpp::operators::{op['name']};"
                for op in op_decorators
                for kind in op["kinds"]
            ),
            delimiter="\n",
        )
