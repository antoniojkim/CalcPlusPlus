# -*- coding: utf-8 -*-

import os
import pathlib
import textwrap

import yaml

try:
    from yaml import CLoader as Loader
except ImportError:
    from yaml import Loader


def wrap(text, width=88, indent="\t", delimiter=", "):
    if not isinstance(text, str):
        text = delimiter.join(text)
    return (os.linesep + indent).join(textwrap.fill(text, width).split(os.linesep))


file_dir = pathlib.Path(__file__).parent.absolute()
template_dir = os.path.join(file_dir, ".templates")

with open(os.path.join(file_dir, "tokens.yml")) as file:
    tokens = yaml.load(file, Loader=Loader)
    # pprint(tokens)

    keys = tuple(list(tokens["specialTokens"]) + list(tokens["operators"].keys()) + list(tokens["tokens"].keys()))

    lexemes = [(operator, vals["lexeme"]) for operator, vals in tokens["operators"].items()] + list(
        tokens["tokens"].items()
    )

    operators = [
        (
            key,
            tokens["operators"].get(key, {}).get("lexeme", ""),
            tokens["operators"].get(key, {}).get("precedence", 0),
            "rightAssociative" in tokens["operators"].get(key, {}),
            "singleOperator" in tokens["operators"].get(key, {}),
        )
        for key in keys
    ]

    functions = [(name, 1 if nargs is None else nargs) for name, nargs in tokens["functions"].items()]
    functions.sort(key=lambda f: (len(f[0]), f[0]), reverse=True)

    functionExprs = set(tokens["functionExprs"])


class Template:
    def __init__(self, template_path, write_path):
        self.template_path = template_path
        self.write_path = write_path

    def __enter__(self):
        with open(self.template_path) as file:
            self.template = file.read()

        return self

    def __exit__(self, type, value, traceback):
        with open(self.write_path, "w") as file:
            file.write(self.template)

    def replace(self, **kwargs):
        for key, val in kwargs.items():
            self.template = self.template.replace(f"{{{key}}}", str(val))


with Template(
    os.path.join(template_dir, "scanner.h"), os.path.join(file_dir, "..", "Scanner", "scanner.h")
) as template:
    template.replace(
        types=wrap(keys, indent="\t\t"), numTokens=len(keys), typeStrings=wrap(map('"{}"'.format, keys), indent="\t\t")
    )


with Template(
    os.path.join(template_dir, "scanner.cc"), os.path.join(file_dir, "..", "Scanner", "scanner.cc")
) as template:
    lexemes.sort(key=lambda l: len(l[1]), reverse=True)
    template.replace(
        numLexemes=len(lexemes),
        lexemes=wrap(map('"{}"'.format, (lexeme for name, lexeme in lexemes))),
        lexemeTypes=wrap((name for name, lexeme in lexemes)),
    )


with Template(
    os.path.join(template_dir, "Operators.h"),
    os.path.join(file_dir, "..", "Expressions", "OperatorExpressions", "Operators.h"),
) as template:
    template.replace(
        operators=wrap((f'"{lexeme}"' for _0, lexeme, _2, _3, _4 in operators)),
        precedences=wrap(
            (
                str(precedence * (1 if rightAssociative else -1))
                for _0, _1, precedence, rightAssociative, _4 in operators
            )
        ),
        singleOperators=wrap(
            (str(int(singleOperator)) for name, lexeme, precedence, rightAssociative, singleOperator in operators)
        ),
        operatorStart=next((i for i, operator in enumerate(operators) if len(operator[1]) > 0)),
        operatorEnd=next((i for i, operator in reversed(list(enumerate(operators))) if len(operator[1]) > 0)),
    )


with Template(
    os.path.join(template_dir, "BinaryOperatorDirectory.cc"),
    os.path.join(file_dir, "..", "Expressions", "OperatorExpressions", "BinaryOperatorDirectory.cc"),
) as template:
    template.replace(
        binaryOperators=wrap(
            (
                f"f_{name}" if lexeme != "" and not singleOperator else "nullptr"
                for name, lexeme, precedence, rightAssociative, singleOperator in operators
            )
        )
    )


with Template(
    os.path.join(template_dir, "Functions.h"),
    os.path.join(file_dir, "..", "Expressions", "FunctionExpressions", "Functions.h"),
) as template:
    template.replace(
        numFunctions=len(functions),
        functionNames=wrap(map('"{}"'.format, (name for name, nargs in functions))),
        functionNameLengths=wrap(map(str, (len(name) for name, nargs in functions))),
        functionNumArgs=wrap(map(str, (nargs for name, nargs in functions))),
    )


with Template(
    os.path.join(template_dir, "FunctionDirectory.cc"),
    os.path.join(file_dir, "..", "Expressions", "FunctionExpressions", "Functions.h"),
) as template:
    template.replace(
        unaryFunctions=wrap(
            (f"f_{name}" if name not in functionExprs and nargs == 1 else "nullptr" for name, nargs in functions)
        ),
        unaryFunctionExprs=wrap(
            (f"fe_{name}" if name in functionExprs and nargs == 1 else "nullptr" for name, nargs in functions)
        ),
    )
    template.replace(
        multiFunctions=wrap(
            (
                f"f_{name}" if name not in functionExprs and (nargs < 0 or nargs > 1) else "nullptr"
                for name, nargs in functions
            )
        ),
        multiFunctionExprs=wrap(
            (f"fe_{name}" if name in functionExprs and nargs != 1 else "nullptr" for name, nargs in functions)
        ),
    )
