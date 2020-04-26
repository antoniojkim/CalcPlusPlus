# -*- coding: utf-8 -*-

from ast import literal_eval

import numpy as np


def numpy_to_string(array):
    array = np.round(array, 10)
    c_array = (
        np.array2string(
            array,
            separator=",",
            formatter={"complexfloat": lambda cf: f"{{{cf.real}, {cf.imag}}}"},
        )
        .replace("[", "{")
        .replace("]", "}")
        .replace("\n", "")
    )

    if len(array.shape) == 2:
        if np.iscomplexobj(array):
            return f"std::vector<std::vector<gsl_complex>>{c_array}"
        else:
            return f"std::vector<std::vector<double>>{c_array}"
    elif len(array.shape) == 1:
        if np.iscomplexobj(array):
            return f"std::vector<gsl_complex>{c_array}"
        else:
            return f"std::vector<double>{c_array}"


def string_to_numpy(string):
    return np.array(
        literal_eval(string.replace("{", "[").replace("}", "]").replace("i", "j"))
    )


def main():
    array = string_to_numpy("{{10, -9i, -12}, {7, -12, 11i}, {-10i, 10, 3}}")
    print(array)
    result = np.linalg.inv(array)
    print(numpy_to_string(result))


if __name__ == "__main__":
    main()
