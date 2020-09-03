# -*- coding: utf-8 -*-

import argparse

from auto_generators.generate_tokens import generate_tokens
from auto_generators.generate_functions import generate_functions

# from auto_generators.generate_random_distributions import generate_random_distributions
from auto_generators.generate_unitconversions import generate_unitconversions


def main(args):
    generate_tokens(args)
    generate_functions(args)
    # generate_random_distributions(args)
    generate_unitconversions(args)

    # functionNames = [alias for alias, name in functions]
    # distributionNames = dists["distributionNames"]
    # constants = tokens["constants"]
    # abbrs = units["abbrs"]

    # assert len(set(functionNames) & set(distributionNames)) == len(distributionNames)
    # assert len(set(abbrs) & set(functionNames)) == 0
    # assert len(set(abbrs) & set(distributionNames)) == 0
    # assert len(set(abbrs) & set(name for name, val in constants)) == 0
    # assert len(set(abbrs)) == len(abbrs)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    main(parser.parse_args())
