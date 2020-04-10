import sys
import numpy as np
from numpy import mean, std, var, sqrt

def function(array):
    a, b, c = tuple(array)
    discriminant = np.round(b*b - 4*a*c, 13)
    if discriminant < 0:
        return "std::vector<double>()"

    x0 = np.round((-b + sqrt(discriminant)) / (2*a), 10)
    if discriminant == 0:
        return f"std::vector<double>{{{x0}, {x0}}}"

    x1 = np.round((-b - sqrt(discriminant)) / (2*a), 10)
    if x1 < x0:
        x0, x1 = x1, x0
        
    return f"std::vector<double>{{{x0}, {x1}}}"

names = ["quad"]

def main():
    for i in range(10):
        if np.random.random() < 0.4:
            a, b = tuple(np.round(np.random.uniform(-10, 10, size=2), 2))
            array = np.round((a*a, 2*a*b, b*b), 13)
        else:
            array = np.round(np.random.uniform(-10, 10, size=3), 2)

        name = names[np.random.randint(len(names))]
        print(f"""
    SECTION("`{name}` Test {i+1}"){{
        requireIsEqual("{name}{tuple(array)}", {function(array)});
    }}""")

if __name__ == "__main__":
    main()
