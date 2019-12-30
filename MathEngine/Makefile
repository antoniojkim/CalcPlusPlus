CXX = g++
CXXFLAGS = -Ofast -g -std=c++17 -fPIC -Wall -MMD -Werror=vla $(shell gsl-config --cflags)
TARGET_LIB = libMathEngine.a  # target lib

MATHENGINE = $(wildcard MathEngine/*.cc)
PARSER = $(wildcard Parser/*.cc)
EXPRESSIONS = $(wildcard Expressions/*/*.cc)

SOURCES = Scanner/scanner.cc ${PARSER} ${EXPRESSIONS} ${MATHENGINE}
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${TARGET_LIB}: ${OBJECTS}
	ar rcs ${TARGET_LIB} ${OBJECTS}

# $(SOURCES:.cc=.d):%.d:%.cc
# 	${CXX} ${CXXFLAGS}  -c $< $@

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean