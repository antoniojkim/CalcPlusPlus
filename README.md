# CalcPlusPlus

Advanced Scientific Calculator written in C++. This calculator is meant to replace my [previous calculator](https://github.com/antoniojkim/Math-Evaluation-Library) which was written using Java.

## Math Engine

The custom built math engine that is used in the CalcPlusPlus project utilizes many of the scientic functions found in the [GNU Scientific Library (GSL)](https://www.gnu.org/software/gsl/). As such, the GSL has to be installed before the project can be built. To do this, run

```
make install
```

## Tests

Unit Tests were written using the [Catch2 Framework](https://github.com/catchorg/Catch2).

To run unit tests, [install Catch2](https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top) and run the `test` script. This will build the compute engine and run the unit tests.
