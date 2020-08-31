cd MathEngine
rm libMathEngine.a
make -f Makefile -j10
cd ../UI
qmake -config release calcpp.pro
make -f Makefile -j10
