import sys
import numpy as np
from numpy import mean, std, var, sqrt

def function(array):
    roots = np.roots(array)
    roots = np.round(roots, 10)
    return f"std::vector<gsl_complex>{{{', '.join(f'gsl_complex{{{root.real}, {root.imag}}}' for root in sorted(roots))}}}"

names = ["quadc"]

def main():
    for i in range(10):
        array = np.round(np.random.uniform(-10, 10, size=3), 2)
        name = names[np.random.randint(len(names))]
        print(f"""
    SECTION("`{name}` Test {i+1}"){{
        requireIsEqual("{name}{tuple(array)}", {function(array)});
    }}""")

if __name__ == "__main__":
    main()
