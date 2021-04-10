BUILD := linux

CXX = clang-10

includes.win := -IC:\DEV\vcpkg\packages\gsl_x64-windows\include
INCLUDES := ${includes.${BUILD}} -I../calcpp

CXXFLAGS = -g -std=c++17 -MMD -Werror=vla -Wall ${INCLUDES}
CPPFLAGS = -DDEBUG
EXEC = tests

SCANNER_TESTS = Tests/ScannerTests/ScannerTests.cc
UTILS_TESTS = $(wildcard Tests/UtilsTests/*.cc)

TESTS = ${SCANNER_TESTS} ${UTILS_TESTS}

SOURCES = Tests/test.cc ${TESTS}
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} \
		-lCatch2Main -lCatch2 \
		-L../calcpp -lcalcpp \
		-lgsl -lgslcblas -lm \
		-lstdc++ \
		-o ${EXEC}


-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
