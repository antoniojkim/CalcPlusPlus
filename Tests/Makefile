BUILD := linux

CXX = g++

includes.linux := -I../.includes/
includes.win := -IC:\DEV\vcpkg\packages\gsl_x64-windows\include
INCLUDES := ${includes.${BUILD}} -I../MathEngine

CXXFLAGS = -g -std=c++17 -MMD -Werror=vla -Wall ${INCLUDES}
CPPFLAGS = -DDEBUG
EXEC = run

TESTS = $(wildcard Tests/*/*.cc)

SOURCES = Tests/EngineTest.cc Tests/test.cc ${TESTS}
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} \
		-L../MathEngine -lMathEngine \
		-L../.libs/ -lgsl -lgslcblas -lm \
		-o ${EXEC}

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
