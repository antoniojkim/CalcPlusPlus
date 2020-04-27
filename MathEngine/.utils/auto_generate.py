# -*- coding: utf-8 -*-

import os
import pathlib
import textwrap

import numpy as np
import yaml

try:
    from yaml import CLoader as Loader
except ImportError:
    from yaml import Loader


def wrap(text, width=88, indent="\t", delimiter=", "):
    if not isinstance(text, str):
        text = delimiter.join(text)
    return (os.linesep + indent).join(textwrap.fill(text, width).split(os.linesep))


def is_newer(file1, file2):
    return os.path.getmtime(file1) > os.path.getmtime(file2)


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


file_dir = pathlib.Path(__file__).parent.absolute()
template_dir = os.path.join(file_dir, ".templates")

if is_newer(
    os.path.join(file_dir, "tokens.yml"),
    os.path.join(file_dir, "..", "Scanner", "scanner.h"),
):
    with open(os.path.join(file_dir, "tokens.yml")) as file:
        tokens = yaml.load(file, Loader=Loader)

        keys = tuple(
            list(tokens["specialTokens"])
            + list(tokens["operators"].keys())
            + list(tokens["tokens"].keys())
        )

        lexemes = [
            (operator, vals["lexeme"]) for operator, vals in tokens["operators"].items()
        ] + list(tokens["tokens"].items())

        operatorLexemes = [
            tokens["operators"].get(key, {}).get("lexeme", "") for key in keys
        ]
        operatorPrecedences = [
            (
                tokens["operators"].get(key, {}).get("precedence", 0),
                "rightAssociative" in tokens["operators"].get(key, {}),
            )
            for key in keys
        ]
        singleOperators = [
            "singleOperator" in tokens["operators"].get(key, {}) for key in keys
        ]
        operatorExprs = [
            "expression" in tokens["operators"].get(key, {}) for key in keys
        ]
        operatorDerivatives = [
            "derivative" in tokens["operators"].get(key, {}) for key in keys
        ]
        operatorIntegrals = [
            "integral" in tokens["operators"].get(key, {}) for key in keys
        ]
        operatorSimplifys = [
            "simplify" in tokens["operators"].get(key, {}) for key in keys
        ]

    with Template(
        os.path.join(template_dir, "scanner.h"),
        os.path.join(file_dir, "..", "Scanner", "scanner.h"),
    ) as template:
        template.replace(
            types=wrap(keys, indent="\t\t"),
            numTokens=len(keys),
            typeStrings=wrap(map('"{}"'.format, keys), indent="\t\t"),
        )

    with Template(
        os.path.join(template_dir, "scanner.cc"),
        os.path.join(file_dir, "..", "Scanner", "scanner.cc"),
    ) as template:
        lexemes.sort(key=lambda l: len(l[1]), reverse=True)
        template.replace(
            numLexemes=len(lexemes),
            lexemes=wrap(map('"{}"'.format, (lexeme for name, lexeme in lexemes))),
            lexemeTypes=wrap((name for name, lexeme in lexemes)),
        )

    with Template(
        os.path.join(template_dir, "Operators.h"),
        os.path.join(
            file_dir, "..", "Expressions", "OperatorExpressions", "Operators.h"
        ),
    ) as template:
        template.replace(
            operators=wrap(map('"{}"'.format, operatorLexemes)),
            precedences=wrap(
                (
                    str(precedence * (1 if rightAssociative else -1))
                    for precedence, rightAssociative in operatorPrecedences
                )
            ),
            singleOperators=wrap(
                (str(int(singleOperator)) for singleOperator in singleOperators)
            ),
            operatorStart=next(
                (i for i, lexeme in enumerate(operatorLexemes) if len(lexeme) > 0)
            ),
            operatorEnd=next(
                (
                    i
                    for i, lexeme in reversed(list(enumerate(operatorLexemes)))
                    if len(lexeme) > 0
                )
            ),
        )

    with Template(
        os.path.join(template_dir, "BinaryOperatorDirectory.cc"),
        os.path.join(
            file_dir,
            "..",
            "Expressions",
            "OperatorExpressions",
            "BinaryOperatorDirectory.cc",
        ),
    ) as template:
        template.replace(
            binaryOperators=wrap(
                (
                    f"f_{name}" if lexeme != "" and not singleOperator else "nullptr"
                    for name, lexeme, singleOperator in zip(
                        keys, operatorLexemes, singleOperators
                    )
                )
            ),
            binaryOperatorExprs=wrap(
                (
                    f"fe_{name}"
                    if expr and lexeme != "" and not singleOperator
                    else "nullptr"
                    for name, lexeme, singleOperator, expr in zip(
                        keys, operatorLexemes, singleOperators, operatorExprs
                    )
                )
            ),
            binaryOperatorDerivatives=wrap(
                (
                    f"fprime_{name}"
                    if derivative and lexeme != "" and not singleOperator
                    else "nullptr"
                    for name, lexeme, singleOperator, derivative in zip(
                        keys, operatorLexemes, singleOperators, operatorDerivatives
                    )
                )
            ),
            binaryOperatorIntegrals=wrap(
                (
                    f"fi_{name}"
                    if integral and lexeme != "" and not singleOperator
                    else "nullptr"
                    for name, lexeme, singleOperator, integral in zip(
                        keys, operatorLexemes, singleOperators, operatorIntegrals
                    )
                )
            ),
            binaryOperatorSimplifys=wrap(
                (
                    f"fs_{name}"
                    if simplify and lexeme != "" and not singleOperator
                    else "nullptr"
                    for name, lexeme, singleOperator, simplify in zip(
                        keys, operatorLexemes, singleOperators, operatorSimplifys
                    )
                )
            ),
        )


if is_newer(
    os.path.join(file_dir, "functions.yml"),
    os.path.join(
        file_dir, "..", "Expressions", "FunctionExpressions", "FunctionDirectory.cc"
    ),
):
    with open(os.path.join(file_dir, "functions.yml")) as file:
        specs = yaml.load(file, Loader=Loader)

        functions = [
            (name, 1 if nargs is None else nargs)
            for name, nargs in specs["functions"].items()
        ]
        functions.sort()

        functionExprs = set(specs["functionExprs"])

    with Template(
        os.path.join(template_dir, "Functions.h"),
        os.path.join(
            file_dir, "..", "Expressions", "FunctionExpressions", "Functions.h"
        ),
    ) as template:
        template.replace(
            numFunctions=len(functions),
            functionNames=wrap(map('"{}"'.format, (name for name, nargs in functions))),
            functionNameLengths=wrap(
                map(str, (len(name) for name, nargs in functions))
            ),
            functionOrderByLength=wrap(
                (
                    str(i)
                    for i, f in sorted(
                        list(enumerate(functions)),
                        key=lambda k: len(k[1][0]),
                        reverse=True,
                    )
                )
            ),
            functionNumArgs=wrap(map(str, (nargs for name, nargs in functions))),
        )

    with Template(
        os.path.join(template_dir, "FunctionDirectory.cc"),
        os.path.join(
            file_dir, "..", "Expressions", "FunctionExpressions", "FunctionDirectory.cc"
        ),
    ) as template:
        template.replace(
            unaryFunctions=wrap(
                (
                    f"f_{name}"
                    if name not in functionExprs and nargs == 1
                    else "nullptr"
                    for name, nargs in functions
                )
            ),
            unaryFunctionExprs=wrap(
                (
                    f"fe_{name}" if name in functionExprs and nargs == 1 else "nullptr"
                    for name, nargs in functions
                )
            ),
        )
        template.replace(
            multiFunctions=wrap(
                (
                    f"f_{name}"
                    if name not in functionExprs and (nargs < 0 or nargs > 1)
                    else "nullptr"
                    for name, nargs in functions
                )
            ),
            multiFunctionExprs=wrap(
                (
                    f"fe_{name}" if name in functionExprs and nargs != 1 else "nullptr"
                    for name, nargs in functions
                )
            ),
        )


if is_newer(
    os.path.join(file_dir, "unitconversions.yml"),
    os.path.join(file_dir, "..", "Expressions", "UnitConversionExpression", "Units.h"),
):
    with open(os.path.join(file_dir, "unitconversions.yml")) as file:
        specs = yaml.load(file, Loader=Loader)
        unitconversions = specs["unitconversions"]

    with Template(
        os.path.join(template_dir, "Units.h"),
        os.path.join(
            file_dir, "..", "Expressions", "UnitConversionExpression", "Units.h"
        ),
    ) as template:
        units = []
        abbrs = []
        unitTypes = []
        conversions = []
        for category, specs in unitconversions["categories"].items():
            base = specs["base"]
            abbr = specs["baseabbr"]
            baseconversion = float(specs.get("baseconversion", 1))
            bc = f"*{1/baseconversion}" if baseconversion != 1 else ""

            units.append(base)
            abbrs.append(abbr)
            unitTypes.append(category)
            conversions.append(1)

            prefixes = specs.get("prefixes", {})
            if "baseprefixes" in specs:
                prefixes.update(unitconversions["prefixes"])

            baseconversion = specs.get("baseconversion", 1)

            units.extend((f"{prefix}{base}" for prefix in prefixes.keys()))
            abbrs.extend((f"{prefix}{abbr}" for prefix in prefixes.values()))
            unitTypes.extend((category for p in prefixes))
            conversions.extend(
                (
                    specs.get("custom", {}).get(
                        prefix, f"GSL_CONST_NUM_{prefix.upper()}"
                    )
                    for prefix in prefixes.keys()
                )
            )

            units.extend(specs.get("conversions", {}).keys())
            abbrs.extend(specs.get("conversions", {}).values())
            unitTypes.extend((category for c in specs.get("conversions", {})))
            conversions.extend(
                (
                    specs.get("custom", {}).get(
                        conv, f"GSL_CONST_MKSA_{conv.upper()}{bc}"
                    )
                    for conv in specs.get("conversions", {}).keys()
                )
            )

        unq, unq_idx, unq_cnt = np.unique(
            abbrs, return_inverse=True, return_counts=True
        )
        assert np.all(unq_cnt == 1), np.array(abbrs)[unq_cnt != 1]

        assert len(set(abbrs) & set(name for name, nargs in functions)) == 0
        assert len(set(abbrs)) == len(abbrs)
        assert len(units) == len(abbrs)
        assert len(units) == len(unitTypes)
        assert len(units) == len(conversions)

        categories = list(unitconversions["categories"].keys())

        unitconversions = list(zip(units, abbrs, unitTypes, conversions))
        unitconversions.sort(key=lambda k: k[1])
        units, abbrs, unitTypes, conversions = zip(*unitconversions)

        units = sorted(enumerate(units), key=lambda k: k[1])

        template.replace(
            UnitTypes=",\n\t".join((c.upper() for c in categories)),
            numUnits=len(units),
            unitNames=wrap((f'"{unit}"' for index, unit in units)),
            unitIndices=wrap((str(index) for index, unit in units)),
            unitAbbreviations=wrap((f'"{abbr}"' for abbr in abbrs)),
            unitTypes=wrap((t.upper() for t in unitTypes)),
            unitConversions=wrap(map(str, conversions)),
        )
