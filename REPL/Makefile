BUILD := linux

CXX = g++

includes.linux := -I../.includes/
includes.win := -IC:\DEV\vcpkg\packages\gsl_x64-windows\include
INCLUDES := ${includes.${BUILD}} -I../MathEngine

CXXFLAGS = -g -std=c++17 -MMD -Werror=vla -Wall ${INCLUDES}
CPPFLAGS = -DDEBUG
EXEC = calc++

SOURCES = repl.cc
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -Wl,--no-undefined \
		 ${OBJECTS} \
		-L../MathEngine -lMathEngine \
		-L../.libs/ -lgsl -lgslcblas -lm \
		-lcurses \
		-o ${EXEC}

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
