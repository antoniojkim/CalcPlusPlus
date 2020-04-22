ifeq ($(CXX),)
CXX := g++
endif

ifeq ($(AR),)
AR := ar
endif

CXXFLAGS = -Ofast -g -std=c++17 -Wall -MMD -Werror=vla -DDEBUG -I../.includes/
TARGET_LIB = libMathEngine.a  # target lib

UTILS = $(wildcard Utils/*.cc)
MATHENGINE = $(wildcard MathEngine/*.cc)
SCANNER = $(wildcard Scanner/*.cc)
PARSER = $(wildcard Parser/*.cc)
EXPRESSIONS = $(wildcard Expressions/*/*.cc)

SOURCES = ${UTILS} ${SCANNER} ${PARSER} ${EXPRESSIONS} ${MATHENGINE}
OBJECTS = $(SOURCES:.cc=.o)
DEPENDS = ${OBJECTS:.o=.d}

${TARGET_LIB}: ${OBJECTS}
	$(AR) rcs ${TARGET_LIB} ${OBJECTS}

win:


# $(SOURCES:.cc=.d):%.d:%.cc
# 	${CXX} ${CXXFLAGS}  -c $< $@

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
