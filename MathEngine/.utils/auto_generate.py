
import os
import pathlib
import textwrap
from pprint import pprint

import yaml
try:
    from yaml import CLoader as Loader, CDumper as Dumper
except ImportError:
    from yaml import Loader, Dumper

def wrap(text, width=80, indent="\t", delimiter=", "):
    if not isinstance(text, str):
        text = delimiter.join(text)
    return (os.linesep + indent).join(textwrap.fill(text, width).split(os.linesep))

file_dir = pathlib.Path(__file__).parent.absolute()
template_dir = os.path.join(file_dir, ".templates")

with open(os.path.join(file_dir, "tokens.yml")) as file:
    tokens = yaml.load(file, Loader=Loader)
    # pprint(tokens)

    keys = tuple(
        list(tokens["specialTokens"]) +
        list(tokens["operators"].keys()) +
        list(tokens["tokens"].keys())
    )

    lexemes = [
        (operator, vals["lexeme"])
        for operator, vals in tokens["operators"].items()
    ] + list(tokens["tokens"].items())

    operators = [
        (
            key,
            tokens["operators"].get(key, {}).get("lexeme", ""),
            tokens["operators"].get(key, {}).get("precedence", 0),
            "rightAssociative" in tokens["operators"].get(key, {}),
            "singleOperator" in tokens["operators"].get(key, {})
        )
        for key in keys
    ]

    functions = [(name, 1 if nargs is None else nargs)
                 for name, nargs in tokens["functions"].items()]
    functions.sort(key=lambda f: (len(f[0]), f[0]), reverse=True)

with open(os.path.join(template_dir, "scanner.h")) as file:
    template = "".join(file)

template = template.replace("{types}", wrap(keys, indent="\t\t"))
template = template.replace("{numTokens}", str(len(keys)))
template = template.replace("{typeStrings}", wrap(map('"{}"'.format, keys), indent="\t\t"))

with open(os.path.join(file_dir, "..", "Scanner", "scanner.h"), "w") as file:
    file.write(template)


with open(os.path.join(template_dir, "scanner.cc")) as file:
    template = "".join(file)

lexemes.sort(key=lambda l: len(l[1]), reverse=True)

template = template.replace("{numLexemes}", str(len(lexemes)))
template = template.replace("{lexemes}", wrap(map('"{}"'.format, (
    lexeme for name, lexeme in lexemes
))))
template = template.replace("{lexemeTypes}", wrap((
    name for name, lexeme in lexemes
)))

with open(os.path.join(file_dir, "..", "Scanner", "scanner.cc"), "w") as file:
    file.write(template)


with open(os.path.join(template_dir, "Operators.h")) as file:
    template = "".join(file)

template = template.replace("{operators}", wrap((
    f'"{lexeme}"'
    for name, lexeme, precedence, rightAssociative, singleOperator in operators
)))
template = template.replace("{precedences}", wrap((
    str(precedence * (1 if rightAssociative else -1))
    for name, lexeme, precedence, rightAssociative, singleOperator in operators
)))
template = template.replace("{singleOperators}", wrap((
    str(int(singleOperator))
    for name, lexeme, precedence, rightAssociative, singleOperator in operators
)))
template = template.replace("{operatorStart}", str(next((
    i for i, operator in enumerate(operators) if len(operator[1]) > 0)
)))
template = template.replace("{operatorEnd}", str(next((
    i for i, operator in reversed(list(enumerate(operators))) if len(operator[1]) > 0)
)))

with open(os.path.join(file_dir, "..", "Expressions", "OperatorExpressions", "Operators.h"), "w") as file:
    file.write(template)


with open(os.path.join(template_dir, "Functions.h")) as file:
    template = "".join(file)

template = template.replace("{numFunctions}", str(len(functions)))
template = template.replace("{functionNames}", wrap(map('"{}"'.format, (
    name for name, nargs in functions
))))
template = template.replace("{functionNameLengths}", wrap(map(str, (
    len(name) for name, nargs in functions
))))
template = template.replace("{functionNumArgs}", wrap(map(str, (
    nargs for name, nargs in functions
))))

with open(os.path.join(file_dir, "..", "Expressions", "FunctionExpressions", "Functions.h"), "w") as file:
    file.write(template)



with open(os.path.join(template_dir, "FunctionDirectory.cc")) as file:
    template = "".join(file)

template = template.replace("{unaryFunctions}", wrap((
    f'f_{name}' if nargs == 1 else "nullptr" for name, nargs in functions
)))

template = template.replace("{multiFunctions}", wrap((
    f'f_{name}' if nargs < 0 or nargs > 1 else "nullptr" for name, nargs in functions
)))

with open(os.path.join(file_dir, "..", "Expressions", "FunctionExpressions", "FunctionDirectory.cc"), "w") as file:
    file.write(template)


with open(os.path.join(template_dir, "BinaryOperatorDirectory.cc")) as file:
    template = "".join(file)

template = template.replace("{binaryOperators}", wrap((
    f'f_{name}' if lexeme != "" and not singleOperator else "nullptr"
    for name, lexeme, precedence, rightAssociative, singleOperator in operators
)))

with open(os.path.join(file_dir, "..", "Expressions", "OperatorExpressions", "BinaryOperatorDirectory.cc"), "w") as file:
    file.write(template)
