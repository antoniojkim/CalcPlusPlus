CXX = g++
CXXFLAGS = -O2 -g -std=c++17 -MMD -Werror=vla $(shell gsl-config --cflags)
EXEC = run

SCANNER_TESTS = $(wildcard ScannerTests/*.cc)

SOURCES = ${SCANNER_TESTS} test.cc 
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -Wl,--no-undefined ${OBJECTS} $(shell gsl-config --libs) -o ${EXEC} -L../MathEngine -lMathEngine

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
