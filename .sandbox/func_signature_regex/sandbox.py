# -*- coding: utf-8 -*-
import re


def main():
    func_signature = re.compile(
        r"// @Function {name}{signature}{aliases}".format(
            name=r"(?P<name>{id})",
            signature=r"\((?P<signature>{id}{arg}(\s*,\s*{id}{arg})*)\)",
            aliases=r"(:(?P<aliases>( *{id})+))?",
        ).format(
            id=r"[a-zA-Z_][a-zA-Z0-9_]*",
            arg=r"((\.\.\.)|(\s*=\s*({num}|None)))?".format(
                num=r"[-+]?[0-9](\.[0-9]+)?(e-?[0-9]+)?"
            ),
        )
    )

    for case in (
        "// @Function neg(x)",
        "// @Function comb(n, r)",
        "// @Function hypot(a...)",
        "// @Function std(a..., ddof=1)",
        "// @Function fcmp(x, y, tol=1e-8)",
        "// @Function deriv(f, x, x1=None)",
        "// @Function LUsolve(A, b): solve",
    ):
        match = func_signature.match(case)
        assert match, f"{case} was not matched"

    with open("../../MathEngine/Functions/Functions/Trigonometry.cc") as file:
        content = file.read()

    curly_braces = []
    depth = 0
    for i, c in enumerate(content):
        if c == "{":
            depth += 1
            curly_braces.append((i, c, depth))
        elif c == "}":
            curly_braces.append((i, c, depth))
            depth -= 1

    decorator_matches = []
    for i in range(1, len(curly_braces)):
        index1, char1, depth1 = curly_braces[i - 1]
        index2, char2, depth2 = curly_braces[i]
        match = func_signature.search(content, index1, index2)

        if match:
            namespace_re = re.compile(f"namespace {match.group('name')}")
            if namespace_re.search(content, index1, index2):
                for j, (index3, char3, depth3) in enumerate(
                    curly_braces[i + 1 :], i + 1
                ):
                    if depth2 == depth3 and char2 != char3:
                        decorator_matches.append((match, i, j))
                        break

    for match, i, j in decorator_matches:
        print(match, i, j)

        index1, char1, depth1 = curly_braces[i]
        index2, char2, depth2 = curly_braces[j]

        print(content[index1 : index2 + 1])


if __name__ == "__main__":
    main()
