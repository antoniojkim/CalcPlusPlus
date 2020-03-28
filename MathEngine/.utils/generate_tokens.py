
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

    precedences = [
        (
            key,
            tokens["operators"].get(key, {}).get("precedence", 0),
            tokens["operators"].get(key, {}).get("rightAssociative", False)
        )
        for key in keys
    ]

    functionNames = tokens["functions"]
    functionNames.sort(key=len, reverse=True)

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

template = template.replace("{numFunctions}", str(len(functionNames)))
template = template.replace("{functionNames}", wrap(map('"{}"'.format, functionNames)))

with open(os.path.join(file_dir, "..", "Scanner", "scanner.cc"), "w") as file:
    file.write(template)



with open(os.path.join(template_dir, "Operators.h")) as file:
    template = "".join(file)

template = template.replace("{precedences}", wrap((
    str(precedence * (1 if rightAssociative else -1))
    for name, precedence, rightAssociative in precedences
)))

with open(os.path.join(file_dir, "..", "Expressions", "Operators.h"), "w") as file:
    file.write(template)
