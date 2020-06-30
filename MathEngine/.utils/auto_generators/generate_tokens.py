# -*- coding: utf-8 -*-
import os

from .Template import wrap, Specifications, Template, file_dir, expr_dir, func_dir


def generate_tokens(args=None):
    with Specifications("tokens.yml") as specs:

        tokens = tuple(specs["tokens"].keys())
        types = tokens + tuple(
            operator
            for operators in specs["operators"]
            for operator in operators.keys()
        )

        with Template(
            "scanner.h", os.path.join(file_dir, "..", "..", "Scanner", "scanner.h"),
        ) as template:
            template.replace(
                types=wrap(types, indent="\t\t"),
                numTokens=len(types),
                typeStrings=wrap(map('"{}"'.format, types), indent="\t\t"),
            )

        with Template(
            "scanner.cc", os.path.join(file_dir, "..", "..", "Scanner", "scanner.cc"),
        ) as template:
            lexemes = [
                (name, lexeme)
                for name, lexeme in specs["tokens"].items()
                if lexeme is not None
            ] + [
                (name, operator["lexeme"])
                for operators in specs["operators"]
                for name, operator in operators.items()
            ]
            lexemes.sort(key=lambda k: k[1])
            template.replace(
                numLexemes=len(lexemes),
                lexemes=wrap(
                    map('"{}"'.format, (lexeme for name, lexeme in lexemes)),
                    indent="\t\t",
                ),
                lexemeTypes=wrap((name for name, lexeme in lexemes), indent="\t\t"),
                longestLexeme=str(max(map(len, lexemes))),
            )

        operators = [
            (
                operator["lexeme"],
                precedence,
                "1" if "singleOperator" in operator else "0",
                "rightAssociative" in operator,
            )
            for precedence, operatorGroup in enumerate(specs["operators"], start=1)
            for name, operator in operatorGroup.items()
        ]
        (
            operatorLexemes,
            operatorPrecedences,
            singleOperators,
            rightAssociatives,
        ) = tuple(zip(*operators))

        with Template(
            "Operators.h", os.path.join(func_dir, "Operators.h"),
        ) as template:
            template.replace(
                numOperators=str(len(operators)),
                operatorOffset=str(len(tokens)),
                operators=wrap(map('"{}"'.format, operatorLexemes), indent="\t\t"),
                precedences=wrap(
                    (
                        str(precedence * (1 if rightAssociative else -1))
                        for _l, precedence, _s, rightAssociative in operators
                    ),
                    indent="\t\t",
                ),
                singleOperators=wrap(singleOperators, indent="\t\t"),
            )

        constants = list(specs["constants"].items())
        constants.sort(key=lambda k: k[0])

        with Template(
            "Constants.h",
            os.path.join(expr_dir, "VariableExpressions", "Constants.h",),
        ) as template:
            template.replace(
                numConstants=len(constants),
                constants=wrap((f'"{name}"' for name, val in constants)),
                constantValues=wrap((str(val["val"]) for name, val in constants)),
                shortConstants=wrap((f'"{val["short"]}"' for name, val in constants)),
                constantLongValues=",\n\t".join(
                    f'"{val["longval"]}"' for name, val in constants
                ),
                shortestConstantName=str(min(len(name) for name, val in constants)),
                longestConstantName=str(max(len(name) for name, val in constants)),
            )

    return locals()


if __name__ == "__main__":
    generate_tokens()
