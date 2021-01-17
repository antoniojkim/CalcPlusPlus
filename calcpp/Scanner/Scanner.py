# -*- coding: utf-8 -*-
import yaml

try:
    from yaml import CLoader as Loader
except ImportError:
    from yaml import Loader


from sourcegen import SourceGenerator
from sourcegen import utils

with open("../symbols.yml") as file:
    symbols = yaml.load(file, Loader)

kinds = symbols["tokens"] + sorted((k for o in symbols["operators"] for k in o.keys()))

if __name__ == "__main__":
    with SourceGenerator("Scanner.h") as source:
        source["kinds"].set_text(kinds, delimiter=",\n")

    with SourceGenerator("Scanner.cc") as source:
        source["kindStrings"].set_text(kinds, quote='"', delimiter=",\n")
        source["inf"].set_text(utils.get_unicode("\N{INFINITY}", "\\u"), quote='"')
