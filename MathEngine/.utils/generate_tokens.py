
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
    
    keys = [next(iter(t.keys())) for t in tokens]
    lexemes = [
        (name, vals["lexeme"])
        for token in tokens
        for name, vals in token.items()
        if "lexeme" in vals
    ]
    regexes = [
        (name, vals["regex"])
        for token in tokens
        for name, vals in token.items()
        if vals.get("regex", None) is not None
    ]
    precedences = [
        (name, vals.get("precedence", 0), vals.get("rightAssociative", False))
        for token in tokens
        for name, vals in token.items()
        if "lexeme" in vals
    ]

with open(os.path.join(template_dir, "scanner.h")) as file:
    template = "".join(file)

template = template.replace("{types}", wrap(keys, indent="\t\t"))
template = template.replace("{numTokens}", str(len(keys)))
template = template.replace("{typeStrings}", wrap(map('"{}"'.format, keys), indent="\t\t"))

with open(os.path.join(file_dir, "..", "Scanner", "scanner.h"), "w") as file:
    file.write(template)


with open(os.path.join(template_dir, "scanner.cc")) as file:
    template = "".join(file)

template = template.replace("{tokenTypes}", ",\n\t".join(
    f'{{"{lexeme}", {name}}}'
    for name, lexeme in lexemes
))
template = template.replace("{regexes}", os.linesep.join(
    f'static const std::regex {name}_regex ("{regex}");'
    for name, regex in regexes 
))

regex_special_chars = {c: r"\\"+c for c in list(r".^$*+-?()[]{}|")}
regex_special_chars["\\"] = r"\\"
regex_special_chars['"'] = r'\"'
replace_special = lambda c: regex_special_chars.get(c, c)

template = template.replace("{token_regex}", "|".join("".join(map(replace_special, list(lexeme))) for name, lexeme in lexemes))
# \\^\\||\\*\\*|//|<<|>>|<-|->|:=|\\\"|\\\\|\\(|\\)|\\[|\\]|\\{|\\}|=|\\+|-|\\*|/|%|\\^|&|\\||~|!|\\.|,|:|;|\\?|#|\\$|'|`|_|C| 

template = template.replace("{regex_searches}", "".join(f"""
    if (std::regex_search(str, match, {name}_regex)){{
        tokens.emplace_back(Token{{match[0], {name}}});
        return Scanner::scan(match.suffix(), tokens);
    }}"""
   for name, regex in regexes
))

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
