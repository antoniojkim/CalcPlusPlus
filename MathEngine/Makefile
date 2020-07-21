CXX := g++

ifeq ($(OS),Windows_NT)
	INCLUDES := -IC:\DEV\vcpkg\packages\gsl_x64-windows\include
	LIB_FLAGS := -shared
	LINK_FLAGS := -Wl,--out-implib,libMathEngine.a -LC:\DEV\vcpkg\packages\gsl_x64-windows\bin
	TARGET_LIB := libMathEngine.dll
else
	INCLUDES := -I../.includes/
	LIB_FLAGS := -fPIC -shared
	LINK_FLAGS := -L../.libs/
	TARGET_LIB := libMathEngine.so
endif

CXXFLAGS := -Ofast -std=c++17 ${LIB_FLAGS} -Wall -MMD -Werror=vla ${INCLUDES}
CPPFLAGS := -DDEBUG

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
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${TARGET_LIB} ${LINK_FLAGS} -lgsl -lgslcblas -lm


# $(SOURCES:.cc=.d):%.d:%.cc
# 	${CXX} ${CXXFLAGS}  -c $< $@

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
