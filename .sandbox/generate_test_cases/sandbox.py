# -*- coding: utf-8 -*-

import numpy as np


def function(arg):
    real = np.real(arg)
    imag = np.imag(arg)
    return f"gsl_complex{{{real}, {imag}}}"


names = ["complex multiplication"]


def main():
    for i in range(10):
        num1 = np.round(np.random.uniform(-10, 10) + np.random.uniform(-10, 10) * 1j, 2)
        num2 = np.round(np.random.uniform(-10, 10) + np.random.uniform(-10, 10) * 1j, 2)
        name = names[np.random.randint(len(names))]
        print(
            f"""
    SECTION("`{name}` Test {i+1}"){{
        requireIsEqual("{num1} / {num2}", {function(np.round(num1/num2, 10))});
    }}"""
        )


if __name__ == "__main__":
    main()
