# -*- coding: utf-8 -*-
import os

from .Template import wrap, Specifications, Template, file_dir, expr_dir


def generate_tokens(args=None):
    with Specifications("tokens.yml") as specs:

        keys = tuple(
            list(specs["specialTokens"])
            + list(specs["operators"].keys())
            + list(specs["tokens"].keys())
        )

        with Template(
            "scanner.h", os.path.join(file_dir, "..", "..", "Scanner", "scanner.h"),
        ) as template:
            template.verify(specs)
            template.replace(
                types=wrap(keys, indent="\t\t"),
                numTokens=len(keys),
                typeStrings=wrap(map('"{}"'.format, keys), indent="\t\t"),
            )

        with Template(
            "scanner.cc", os.path.join(file_dir, "..", "..", "Scanner", "scanner.cc"),
        ) as template:
            template.verify(specs)
            lexemes = [
                (operator, vals["lexeme"])
                for operator, vals in specs["operators"].items()
            ] + list(specs["tokens"].items())
            lexemes.sort(key=lambda l: len(l[1]), reverse=True)
            template.replace(
                numLexemes=len(lexemes),
                lexemes=wrap(map('"{}"'.format, (lexeme for name, lexeme in lexemes))),
                lexemeTypes=wrap((name for name, lexeme in lexemes)),
            )

        operatorLexemes = [
            specs["operators"].get(key, {}).get("lexeme", "") for key in keys
        ]
        operatorPrecedences = [
            (
                specs["operators"].get(key, {}).get("precedence", 0),
                "rightAssociative" in specs["operators"].get(key, {}),
            )
            for key in keys
        ]

        def operators_constains(conditionKey):
            return [conditionKey in specs["operators"].get(key, {}) for key in keys]

        singleOperators = operators_constains("singleOperator")
        operatorExprs = operators_constains("expression")
        operatorDerivatives = operators_constains("derivative")
        operatorSimplifys = operators_constains("simplify")

        with Template(
            "Operators.h", os.path.join(expr_dir, "OperatorExpressions", "Operators.h"),
        ) as template:
            template.verify(specs)
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
            "BinaryOperatorDirectory.cc",
            os.path.join(
                expr_dir, "OperatorExpressions", "BinaryOperatorDirectory.cc",
            ),
        ) as template:
            template.verify(specs)
            template.replace(
                binaryOperators=wrap(
                    (
                        f"f_{name}"
                        if lexeme != "" and not singleOperator
                        else "nullptr"
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

        constants = list(specs["constants"].items())
        constants.sort(key=lambda k: k[0])

        with Template(
            "Constants.h",
            os.path.join(expr_dir, "VariableExpressions", "Constants.h",),
        ) as template:
            template.verify(specs)
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
