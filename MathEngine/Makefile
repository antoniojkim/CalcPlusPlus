CXX = g++
CXXFLAGS = -Ofast -g -std=c++17 -fPIC -Wall -MMD -Werror=vla
TARGET_LIB = libMathEngine.a  # target lib

SOURCES = Scanner/scanner.cc Parser/parsetree.cc Parser/parser.cc MathEngine/MathEngine.cc
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${TARGET_LIB}: ${OBJECTS}
	ar rcs ${TARGET_LIB} ${OBJECTS}

$(SOURCES:.cc=.d):%.d:%.cc
	${CXX} ${CXXFLAGS} $(shell gsl-config --cflags) -c $< -o >$@

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean