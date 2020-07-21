cd MathEngine
rm libMathEngine.dll
make -f Makefile -j10
cd ../CalcUI
qmake -config release CalcUI.pro
make -f Makefile -j10
