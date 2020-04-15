CXX = g++
CXXFLAGS = -Ofast -g -std=c++17 -fPIC -Wall -MMD -Werror=vla -DDEBUG -I../.includes/
TARGET_LIB = libMathEngine.a  # target lib

MATHENGINE = $(wildcard MathEngine/*.cc)
SCANNER = $(wildcard Scanner/*.cc)
PARSER = $(wildcard Parser/*.cc)
EXPRESSIONS = $(wildcard Expressions/*/*.cc)

SOURCES = ${SCANNER} ${PARSER} ${EXPRESSIONS} ${MATHENGINE}
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
