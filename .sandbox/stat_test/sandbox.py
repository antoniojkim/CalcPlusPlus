# -*- coding: utf-8 -*-
import numpy as np


def function(array):
    roots = np.roots(array)
    roots = np.round(roots, 10)
    roots = ", ".join(f"{{{root.real}, {root.imag}}}" for root in sorted(roots))
    return f"std::vector<gsl_complex>{{{roots}}}"


names = ["integral"]


def main():
    for i in range(10):
        array = np.round(np.random.uniform(-10, 10, size=3), 2)
        name = names[np.random.randint(len(names))]
        print(
            f"""
    SECTION("`{name}` Test {i+1}"){{
        requireIsEqual("{name}{tuple(array)}", {function(array)});
    }}"""
        )


if __name__ == "__main__":
    main()
