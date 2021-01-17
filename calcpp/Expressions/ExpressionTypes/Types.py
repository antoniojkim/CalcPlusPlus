# -*- coding: utf-8 -*-
from sourcegen import SourceGenerator

types = [
    "NONE",
    "EMPTY",
    "INVALID",
    "NUM",
    "COMPLEX",
    "HEX",
    "BIN",
    "VAR",
    "VARARG",
    "CONSTANT",
    "TUPLE",
    "MATRIX",
    "STRING",
    "CALLABLE",
    "EVALUABLE",
]

if __name__ == "__main__":
    maxlen = max(map(len, types))
    values = [
        f"{t: <{maxlen}} = {1 << i:#0{len(types) + 2}b}" for i, t in enumerate(types)
    ]

    with SourceGenerator("Types.h") as source:
        source["types"].set_text(values, delimiter=",\n")
