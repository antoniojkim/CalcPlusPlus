CXX = g++
CXXFLAGS = -O2 -g -std=c++17 -MMD -Werror=vla $(shell gsl-config --cflags) -I../MathEngine
EXEC = run

SCANNER_TESTS = $(wildcard ScannerTests/*.cc)
# PARSER_TESTS = $(wildcard ParserTests/*.cc)
# BASIC_TESTS = $(wildcard BasicTests/*.cc)

SOURCES = ${SCANNER_TESTS} ${PARSER_TESTS} ${BASIC_TESTS} EngineTest.cc test.cc 
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -Wl,--no-undefined ${OBJECTS} \
		-L../includes/.gsl_libs/ -l:libgsl.a \
		-L../includes/.cblas_libs/ -l:libgslcblas.a -lm \
		-o ${EXEC} -L../MathEngine -lMathEngine

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
