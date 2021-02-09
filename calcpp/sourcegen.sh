#!/bin/bash

DIR=$(pwd)

cd $DIR/Scanner/
python Scanner.py
python GreekLetters.py

cd $DIR/Functions/
python Functions.py
python Operators.py

cd $DIR/Expressions/VariableExpressions/
python Constants.py

cd $DIR/Expressions/ExpressionTypes/
python Types.py
