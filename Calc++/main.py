# -*- coding: utf-8 -*-
import argparse

from Calcpp.REPL import repl_main


def main(args):
    repl_main(args)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    main(parser.parse_args())
