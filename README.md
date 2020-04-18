# CalcPlusPlus

Advanced Scientific Calculator written in C++. This calculator is meant to replace my [previous calculator](https://github.com/antoniojkim/Math-Evaluation-Library) which was written using Java.

## Table of Contents

* [Requirements](#Requirements)
* [Build](#Build)
* [Tests](#Tests)
* [Tutorial](#Tutorial)

## Requirements

All packages required to build the project can be installed using the following command:

```
make requirements install
```

### GNU Scientific Library

The custom built math engine that is used in the CalcPlusPlus project utilizes many of the scientic functions found in the [GNU Scientific Library (GSL)](https://www.gnu.org/software/gsl/).

## Build

To build and run the GUI application, simply use the following command:

```
make run
```

## Tests

Unit Tests were written using the [Catch2 Framework](https://github.com/catchorg/Catch2).

To run unit tests:

```
make test
```

## Tutorial

Here are some simple examples of the syntax the MathEngine accepts:

```
1 / 2 - 3 * 4 + 5 = -6.5
```

### Matrix

```
{{0.11, 0.12, 0.13}, {0.21, 0.22, 0.23}} * {{1011, 1012}, {1021, 1022}, {1031, 1032}} = {{367.76, 368.12}, {674.06, 674.72}}
```

### Tuple

```
(1, 2, 3, 4)
```
