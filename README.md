# CalcPlusPlus

[![Documentation Status](https://readthedocs.org/projects/calcplusplus/badge/?version=latest)](https://calcplusplus.readthedocs.io/en/latest/?badge=latest)

Advanced Scientific Calculator written in C++. This calculator is meant to replace my [previous calculator](https://github.com/antoniojkim/Math-Evaluation-Library) which was written using Java.

## Installation

### Homebrew (Mac OS X)

[Homebrew](brew.sh) can be used to install the Mac OS version of the calculator using the following cask formula:

```bash
brew cask install antoniojkim/public/calcpp
# or to update the calculator
brew reinstall antoniojkim/public/calcpp
```

### Linux/Windows

Download the OS appropriate version from the [release page](https://github.com/antoniojkim/CalcPlusPlus/releases/)
  - [Linux](https://github.com/antoniojkim/CalcPlusPlus/releases/download/v0.3/calcplusplus.tar.gz)
    - `Calculator.sh` is the executable script
  - [Windows](https://github.com/antoniojkim/CalcPlusPlus/releases/download/v0.4/CalcPlusPlus.zip)
    - `Calculator.exe` is the executable

## Getting Started and Documentation

The primary documentation for this repository can be found at https://calcplusplus.readthedocs.io/en/latest/

## Modified Shunting Yard

The CalcPlusPlus engine was designed for fast real time parsing and expression evaluation. Using a traditional look-ahead parser would be too slow for this use case, so the CalcPlusPlus engine instead utilizes a new modification of Dijkstra's [Shunting Yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm). While Dijkstra's algorithm is simple and efficient, it is lacking the parsing capabilities that most modern scientific calculators need. So, I propose a modification that extends the origial algorithm to accept functions, tuples and matrix syntax.

### The Algorithm

The main idea behind the shunting yard algorithm is to convert infix notation math into postfix notation for easy expression evaluation without needing to worry about the order of operators. This new algorithm serves to extend this idea using context scopes.

The shunting yard algorithm is stack-based. In the original algorithm there are two stacks that are used, and output stack as well as an operator stack. In the new algorithm, we take this idea and instead of just using two stacks, we use two stacks of stacks. The main idea is that we introduce a new set of stacks for every new parsing context we encounter.

For example, take the expression `1 * 2 + sin(3 / 4)`. Dijsktra's shunting yard algorithm does not handle this case as it involves a function, namely `sin`. To handle this, we create a stack for the original overarching context and add stacks according to any new contexts that we encounter.
