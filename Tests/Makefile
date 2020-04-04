CXX = g++
CXXFLAGS = -O2 -g -std=c++17 -MMD -Werror=vla -Wall -I../.includes/ -I../MathEngine
EXEC = run

SCANNER_TESTS = $(wildcard ScannerTests/*.cc)
POSTFIX_TESTS = $(wildcard PostfixTests/*.cc)
PARSER_TESTS = $(wildcard ParserTests/*.cc)
BASIC_TESTS = $(wildcard BasicTests/*.cc)

SOURCES = ${SCANNER_TESTS} ${POSTFIX_TESTS} ${PARSER_TESTS} ${BASIC_TESTS} EngineTest.cc test.cc 
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -Wl,--no-undefined \
		 ${OBJECTS} \
		-L../MathEngine -lMathEngine \
		-L../.libs/ -lgsl -lgslcblas -lm \
		-o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
