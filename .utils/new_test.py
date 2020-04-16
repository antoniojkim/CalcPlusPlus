# -*- coding: utf-8 -*-

import argparse
import os


def main(args):
    name = args.name
    if not os.path.isdir(f"Tests/Tests/{name}"):
        os.mkdir(f"Tests/Tests/{name}")

    with open(".utils/.templates/new_test.cc") as file:
        template = "".join(file)

    template = template.replace("{name}", name)

    with open(f"Tests/Tests/{name}/{name}.cc", "w") as file:
        file.write(template)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--name", help="name of test")

    main(parser.parse_args())
