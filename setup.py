# -*- coding: utf-8 -*-
import setuptools

setuptools.setup(
    name="calcpp",
    version="0.0.1",
    author="Antonio J Kim",
    author_email="contact@antoniojkim.com",
    description="A robust Math evaluation engine that comes with a custom REPL and UI",
    url="https://github.com/antoniojkim/CalcPlusPlus",
    packages=["calcpp", "calcpp/calcpp"],
    package_dir={"calcpp": "calcpp", "calcpp/calcpp": "calcpp/calcpp"},
    package_data={"calcpp": ["libMathEngine.so", "libgsl.so.25", "libgslcblas.so.0"]},
    # include_package_data=True,
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.6",
    install_requires=["prompt_toolkit", "pyqt5"],
    entry_points={"console_scripts": ["calcpp = calcpp.main:main"]},
)
