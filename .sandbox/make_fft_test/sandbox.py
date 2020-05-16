# -*- coding: utf-8 -*-

import numpy as np


def numpy_to_string(array):
    return (
        np.array2string(
            array,
            separator=", ",
            formatter={
                "complexfloat": lambda cf: "".join(
                    str(cf.real),
                    "+" if cf.imag > 0 else "",
                    f"{cf.imag}i" if cf.imag != 0 else "",
                )
            },
        )
        .replace("[", "{")
        .replace("]", "}")
        .replace("\n", " ")
        .replace("  ", " ")
        .replace("{ ", "{")
        .replace(" }", "}")
    )


def function(array):
    result = np.round(np.fft.ifft(array), 10)
    return f'"{numpy_to_string(result)}"'


names = ["ifft"]


def main():
    for i in range(10):
        num = np.random.randint(2, 17)
        array = np.round(
            np.random.uniform(-10, 10, size=num)
            + np.random.uniform(-10, 10, size=num) * 1j,
            2,
        )
        name = names[np.random.randint(len(names))]
        print(
            f'requireExprIsEqual("{name}{numpy_to_string(array)}", {function(array)});'
        )
        print()


def test_fft2_definition():
    n = np.random.randint(2, 7)
    m = np.random.randint(2, 7)
    array = np.round(np.random.uniform(-10, 10, size=(n, m)), 2)
    print(array)


if __name__ == "__main__":
    main()
    # test_fft2_definition()
