cd MathEngine
rm libMathEngine.a
make -f Makefile -j10
cd ../CalcUI
qmake -config release CalcUI.pro
make -f Makefile -j10
