# -*- coding: utf-8 -*-

import numpy as np


def numpy_to_string(array):
    return (
        np.array2string(
            array,
            separator=",",
            formatter={"complexfloat": lambda cf: f"{{{cf.real}, {cf.imag}}}"},
        )
        .replace("[", "{")
        .replace("]", "}")
    )


def function(array):
    result = np.round(np.fft.fft(array), 10)
    return f"std::vector<std::vector<gsl_complex>>{numpy_to_string(result)}"


names = ["ifft"]


def main():
    for i in range(1):
        num = np.random.randint(2, 17)
        array = np.round(
            np.random.uniform(-10, 10, size=num)
            + np.random.uniform(-10, 10, size=num) * 1j,
            2,
        )
        name = names[np.random.randint(len(names))]
        args = ", ".join(map(str, array))
        print(f'requireIsEqual("{name}{{{args}}}", {function(array)});')
        print()


def test_fft2_definition():
    n = np.random.randint(2, 7)
    m = np.random.randint(2, 7)
    array = np.round(np.random.uniform(-10, 10, size=(n, m)), 2)
    print(array)


if __name__ == "__main__":
    main()
    # test_fft2_definition()
