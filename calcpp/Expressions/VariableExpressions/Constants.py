# -*- coding: utf-8 -*-
from sourcegen import SourceGenerator

constants = {
    "pi": {
        "repr": "π",
        "val": "M_PI",
        "longval": "3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328",  # noqa: E501
    },
    "e": {
        "repr": "e",
        "val": "M_E",
        "longval": "2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427427466391932",  # noqa: E501
    },
    "gamma": {  # Euler–Mascheroni constant
        "repr": "γ",
        "val": "M_EULER",
        "longval": "0.5772156649015328606065120900824024310421593359399235988057672348848677267776646709369470632917467495146314472498",  # noqa: E501
    },
    "vphi": {  # Golden Ratio
        "repr": "ϕ",
        "val": "1.6180339887498948482",
        "longval": "1.61803398874989484820458683436563811772030917980576286213544862270526046281890244970720720418939113748475408807538",  # noqa: E501
    },
}

if __name__ == "__main__":
    names = []
    reprs = []
    values = []
    longvals = []
    for name, v in constants.items():
        names.append(name)
        reprs.append(v["repr"])
        values.append(v["val"])
        longvals.append(v["longval"])

    with SourceGenerator("Constants.h") as source:
        source["numConstants"].set_text(len(constants))
        source["constants"].set_text(names, quote='"', delimiter=", ")
        source["constantValues"].set_text(values, delimiter=", ")
        source["shortConstants"].set_text(reprs, quote='"', delimiter=", ")
        source["constantLongValues"].set_text(longvals, quote='"', delimiter=",\n")
        source["longestConstantName"].set_text(max(map(len, names)))
        source["shortestConstantName"].set_text(min(map(len, names)))
