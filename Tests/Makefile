CXX = g++
CXXFLAGS = -O2 -g -std=c++17 -MMD -Werror=vla -Wall $(shell gsl-config --cflags) -I../MathEngine
EXEC = run

SCANNER_TESTS = $(wildcard ScannerTests/*.cc)
POSTFIX_TESTS = $(wildcard PostfixTests/*.cc)
BASIC_TESTS = $(wildcard BasicTests/*.cc)

SOURCES = ${SCANNER_TESTS} ${POSTFIX_TESTS} ${BASIC_TESTS} EngineTest.cc test.cc 
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -Wl,--no-undefined ${OBJECTS} \
		-L../.includes/.gsl_libs/ -L../.includes/.cblas_libs/ -L../MathEngine \
		-lgsl -lgslcblas -lm -lMathEngine \
		-o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
