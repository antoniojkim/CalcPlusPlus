CXX := g++

ifeq ($(OS),Windows_NT)
	INCLUDES := -IC:\DEV\vcpkg\packages\gsl_x64-windows\include
else
	INCLUDES := -I../.includes/
endif

CXXFLAGS := -Ofast -g -std=c++17 -fPIC -shared -Wall -MMD -Werror=vla ${INCLUDES}
CPPFLAGS := -DDEBUG
TARGET_LIB := libMathEngine.so  # target lib

UTILS := $(wildcard Utils/*.cc)
MATHENGINE := $(wildcard MathEngine/*.cc)
SCANNER := $(wildcard Scanner/*.cc)
PARSER := $(wildcard Parser/*.cc)
EXPRESSIONS := $(wildcard Expressions/*/*.cc)
FUNCTIONS := $(wildcard Functions/*.cc)
FUNCTIONIMPL := $(wildcard Functions/*/*.cc)

SOURCES := ${UTILS} ${SCANNER} ${PARSER} ${EXPRESSIONS} ${FUNCTIONS} ${FUNCTIONIMPL} ${MATHENGINE}
OBJECTS := ${SOURCES:.cc=.o}
DEPENDS := ${OBJECTS:.o=.d}

${TARGET_LIB}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${TARGET_LIB} -L../.libs/ -lgsl -lgslcblas -lm


# $(SOURCES:.cc=.d):%.d:%.cc
# 	${CXX} ${CXXFLAGS}  -c $< $@

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
