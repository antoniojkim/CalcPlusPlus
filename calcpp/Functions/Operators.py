# -*- coding: utf-8 -*-
import yaml

try:
    from yaml import CLoader as Loader
except ImportError:
    from yaml import Loader


from sourcegen import SourceGenerator

with open("../symbols.yml") as file:
    symbols = yaml.load(file, Loader)


if __name__ == "__main__":
    operators = symbols["operators"]

    opinfo = [
        (
            operator,
            (
                (i + 1)
                * (1 if metadata is not None and "rightAsociative" in metadata else -1),
                (1 if metadata is not None and "singleOperator" in metadata else 0),
            ),
        )
        for i, group in enumerate(operators)
        for operator, metadata in group.items()
    ]
    opinfo.sort()

    with SourceGenerator("Operators.cc") as source:
        source["size"].set_text(len(operators))
        source["offset"].set_text(len(symbols["tokens"]))

        source["precedences"].set_text(
            (str(p) for op, (p, s) in opinfo), delimiter=", ", wrap_width=80
        )
        source["single"].set_text(
            (str(s) for op, (p, s) in opinfo), delimiter=", ", wrap_width=80
        )
