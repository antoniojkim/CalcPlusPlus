# -*- coding: utf-8 -*-

import numpy as np


def complex_to_string(array):
    return ", ".join(
        f"{{{real}, {imag}}}" for real, imag in zip(array.real, array.imag)
    )


def function(array):
    result = np.round(np.fft.ifft(array), 10)
    return f"std::vector<std::vector<gsl_complex>>{{{{{complex_to_string(result)}}}}}"


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
        args = ", ".join(map(str, array))
        print(f'requireIsEqual("{name}{{{args}}}", {function(array)});')
        print()


if __name__ == "__main__":
    main()
