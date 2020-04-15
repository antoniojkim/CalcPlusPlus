CXX = g++
CXXFLAGS = -O2 -g -std=c++17 -MMD -Werror=vla -Wall -DDEBUG -I../.includes/ -I../MathEngine
EXEC = run

TESTS = $(wildcard Tests/*/*.cc)

SOURCES = ${TESTS} Tests/EngineTest.cc Tests/test.cc
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
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
