import sys
import numpy as np
from numpy import mean, std, var

def function(array):
    return mean(array)

names = ["mean"]

def main():
    for i in range(10):
        array = np.round(np.random.uniform(-10, 10, size=np.random.randint(2, 10)), 2)
        name = names[np.random.randint(len(names))]
        print(f"""
    SECTION("`{name}` Test {i+1}"){{
        requireIsEqual("{name}{tuple(array)}", {np.round(function(array), 10)});
    }}""")

if __name__ == "__main__":
    main()
