CXX := g++
AR := ar

ifeq ($(OS),Windows_NT)
	INCLUDES := -IC:\DEV\vcpkg\packages\gsl_x64-windows\include
else
	INCLUDES := -I../.includes/
endif

CXXFLAGS = -Ofast -g -std=c++17 -fPIC -Wall -MMD -Werror=vla ${INCLUDES}
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


# $(SOURCES:.cc=.d):%.d:%.cc
# 	${CXX} ${CXXFLAGS}  -c $< $@

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
