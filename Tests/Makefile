BUILD := linux

CXX = g++

includes.linux := -I../.includes/
includes.win := -IC:\DEV\vcpkg\packages\gsl_x64-windows\include
INCLUDES := ${includes.${BUILD}} -I../

CXXFLAGS = -g -std=c++17 -MMD -Werror=vla -Wall ${INCLUDES}
CPPFLAGS = -DDEBUG
EXEC = tests

SCANNER_TESTS = ../calcpp/Scanner/Scanner.cc Tests/ScannerTests/ScannerTests.cc
UTILS_TESTS = $(wildcard Tests/UtilsTests/*.cc)

TESTS = ${SCANNER_TESTS} ${UTILS_TESTS}

SOURCES = Tests/test.cc ${TESTS}
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} \
		-lCatch2Main -lCatch2 \
		-o ${EXEC}

# -L../MathEngine -lMathEngine \
# -L../.libs/ -lgsl -lgslcblas -lm \

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
