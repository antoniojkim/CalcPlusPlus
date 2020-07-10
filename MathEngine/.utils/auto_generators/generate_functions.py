# -*- coding: utf-8 -*-
import os
import re

from .Template import wrap, Template, func_dir


func_signature = re.compile(
    r"// @Function {name}{signature}{aliases}".format(
        name=r"(?P<name>{id})",
        signature=r"\((?P<signature>{id}{arg}(\s*,\s*{id}{arg})*)?\)",
        aliases=r"(:(?P<aliases>( *{id})+))?",
    ).format(
        id=r"[a-zA-Z_][a-zA-Z0-9_]*",
        arg=r"((\.\.\.)|(\s*=\s*({num}|None)))?".format(
            num=r"[-+]?[0-9](\.[0-9]+)?(e-?[0-9]+)?"
        ),
    )
)
op_signature = re.compile(
    r"// @Operator {name}{aliases}".format(
        name=r"(?P<name>[a-zA-Z_][a-zA-Z0-9_]*)", aliases=r"(:(?P<aliases>( *\S+)+))?",
    )
)
method_types = (
    ("eval", "expression"),
    ("value", "double"),
    ("simplify", "expression"),
    ("derivative", "expression"),
    ("integral", "expression"),
    ("print", "std::ostream&"),
    ("postfix", "std::ostream&"),
)
method_decls = tuple(
    (
        (
            method,
            f"{ret} {method_decl.format(method)}",
            f"{method.upper()}_DECLARATION{suffix}()",
        )
        for method, ret in method_types
        for method_decl, suffix in zip(("{}", "(*{})"), ("", "_P"))
    )
) + (
    ("eval", "STAT_EVAL", "STAT_EVAL_DECLARATION()"),
    ("print", "OPERATOR_PRINT_POSTFIX_DEFINITION", "PRINT_DECLARATION()"),
    ("postfix", "OPERATOR_PRINT_POSTFIX_DEFINITION", "POSTFIX_DECLARATION()"),
)


def parse_contents(contents):
    curly_braces = []
    depth = 0
    for i, c in enumerate(contents):
        if c == "{":
            curly_braces.append((i, c, depth))
            depth += 1
        elif c == "}":
            depth -= 1
            curly_braces.append((i, c, depth))

    def search_methods(func_dict, i):
        index1, char1, depth1 = curly_braces[i - 1]
        index2, char2, depth2 = curly_braces[i]
        name = func_dict["name"].strip()
        namespace_re = re.compile(f"namespace {name}")
        if namespace_re.search(contents, index1, index2):
            index3, char3, depth3 = next(
                curly_braces[j]
                for j in range(i + 1, len(curly_braces))
                if depth2 == curly_braces[j][2] and char2 != curly_braces[j][1]
            )
            namespace = contents[index2 : index3 + 1]
            found_types = [(mt, decl) for mt, s, decl in method_decls if s in namespace]
            return [
                {
                    "name": name,
                    "signature": func_dict["signature"],
                    "aliases": func_dict["aliases"],
                    "methods": {mt for mt, decl in found_types},
                    "declarations": sorted({decl for mt, decl in found_types}),
                }
            ]

        return []

    functions = []
    for i in range(1, len(curly_braces)):
        index1, char1, depth1 = curly_braces[i - 1]
        index2, char2, depth2 = curly_braces[i]
        match = func_signature.search(contents, index1, index2)

        if match:
            functions.extend(
                search_methods(
                    {
                        "name": match.group("name"),
                        "signature": match.group("signature"),
                        "aliases": match.group("aliases"),
                    },
                    i,
                )
            )
        else:
            match = op_signature.search(contents, index1, index2)
            if match:
                functions.extend(
                    search_methods(
                        {
                            "name": match.group("name"),
                            "signature": "l, r",
                            "aliases": match.group("aliases"),
                        },
                        i,
                    )
                )

    return functions


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
            functions.extend(parse_contents(file.read()))

    signatures = {}
    unique_args = {}

    def generate_signature(function):
        nonlocal unique_args
        if function["signature"]:
            args = function["signature"].split(", ")
            num_pos = 0
            has_varargs = "f"
            default_args = []
            for arg in args:
                if arg.endswith("..."):
                    has_varargs = "t"
                elif "=" in arg:
                    val = arg.split("=")[1].strip()
                    default_args.append("GSL_NAN" if val == "None" else val)
                else:
                    num_pos += 1

            default_args = tuple(default_args)
            for arg in default_args:
                if arg not in unique_args:
                    unique_args[arg] = str(len(unique_args))

            hash = "_".join(map(unique_args.get, default_args))

            key = f"sig_{num_pos}_{has_varargs}_{hash}"
            if key not in signatures:
                varargs = "true" if has_varargs == "t" else "false"
                init = f"{num_pos}, {varargs}, {{{', '.join(default_args)}}}"
                signatures[key] = f"const Function::Signature {key}({init});"
            return key

        else:
            signatures["sig_0"] = "const Function::Signature sig_0(0, false, {});"
            return "sig_0"

    def get_all():
        for function in functions:
            signature = generate_signature(function)
            yield function["name"], function["name"], function["methods"], signature
            if function["aliases"] is not None:
                for alias in function["aliases"].split():
                    if len(alias.strip()) > 0:
                        yield alias.strip(), function["name"], function[
                            "methods"
                        ], signature

    all_names, all_refs, all_methods, all_signatures = zip(*sorted(get_all()))

    declarations = []
    for function in functions:
        methods = "\n\t\t".join(function["declarations"])
        declarations.append(f"\tnamespace {function['name']} {{\n\t\t{methods}\n\t}}")

    with Template("Functions.h", os.path.join(func_dir, "Functions.h")) as template:
        template.replace(
            numFunctions=len(all_names),
            names=wrap(map('"{}"'.format, all_names), indent="\t\t"),
            declarations="\n".join(declarations),
        )

    def get_refs(method):
        for ref, methods in zip(all_refs, all_methods):
            if method in methods:
                yield f"{ref}::{method}"
            else:
                yield "nullptr"

    with Template("Functions.cc", os.path.join(func_dir, "Functions.cc")) as template:
        template.replace(
            EvalFunctions=wrap(", ".join(get_refs("eval")), indent="\t\t"),
            ValueFunctions=wrap(", ".join(get_refs("value")), indent="\t\t"),
            SimplifyFunctions=wrap(", ".join(get_refs("simplify")), indent="\t\t"),
            DerivativeFunctions=wrap(", ".join(get_refs("derivative")), indent="\t\t"),
            IntegralFunctions=wrap(", ".join(get_refs("integral")), indent="\t\t"),
            PrintFunctions=wrap(", ".join(get_refs("print")), indent="\t\t"),
            PostfixFunctions=wrap(", ".join(get_refs("postfix")), indent="\t\t"),
            signatureDefs="\n\t".join(signatures.values()),
            Signatures=wrap(
                ", ".join(map("&{}".format, all_signatures)), indent="\t\t"
            ),
        )


if __name__ == "__main__":
    generate_functions()
