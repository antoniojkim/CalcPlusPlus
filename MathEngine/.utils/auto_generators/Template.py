# -*- coding: utf-8 -*-

import os
import pathlib
import textwrap

import yaml

try:
    from yaml import CLoader as Loader
except ImportError:
    from yaml import Loader


file_dir = pathlib.Path(__file__).parent.absolute()
expr_dir = os.path.join(file_dir, "..", "..", "Expressions")
func_dir = os.path.join(file_dir, "..", "..", "Functions")


def wrap(text, width=88, indent="\t", delimiter=", "):
    if not isinstance(text, str):
        text = delimiter.join(text)
    return (os.linesep + indent).join(textwrap.fill(text, width).split(os.linesep))


class Specifications:
    spec_dir = os.path.join(file_dir, "..", ".specs")

    def __init__(self, spec_file):
        self.spec_path = os.path.join(self.spec_dir, spec_file)

    def __enter__(self):
        with open(self.spec_path) as file:
            self.specs = yaml.load(file, Loader=Loader)

        return self

    def __exit__(self, type, value, traceback):
        pass

    def __getitem__(self, key):
        return self.specs[key]


def is_newer(file1, file2):
    return (
        not os.path.isfile(file1)
        or not os.path.isfile(file2)  # noqa: W503
        or os.path.getmtime(file1) > os.path.getmtime(file2)  # noqa: W503
    )


class Template:
    template_dir = os.path.join(file_dir, "..", ".templates")

    def __init__(self, template_file: str, write_path: str):
        self.template_path = os.path.join(self.template_dir, template_file)
        self.write_path = write_path

    def __enter__(self):
        with open(self.template_path) as file:
            self.template = file.read()

        return self

    def __exit__(self, type, value, traceback):
        if type is None and value is None and traceback is None:
            if os.path.isfile(self.write_path):
                with open(self.write_path) as file:
                    old_template = file.read()
            else:
                old_template = ""

            if old_template != self.template:
                print(f"Generating {self.write_path}")
                with open(self.write_path, "w") as file:
                    file.write(self.template)

        else:
            print(traceback)

        return True

    def replace(self, **kwargs):
        for key, val in kwargs.items():
            self.template = self.template.replace(f"{{{key}}}", str(val))
