CXX := g++

mode := release
optflag.release := -g -Ofast
optflag.debug := -g
OPT_FLAG := ${optflag.${mode}}

ifeq ($(OS),Windows_NT)
	INCLUDES := -IC:\DEV\vcpkg\packages\gsl_x64-windows\include
	LIB_FLAGS := -fPIC -static
	LINK_FLAGS := -LC:\DEV\vcpkg\packages\gsl_x64-windows\bin
	TARGET_LIB := libMathEngine.a
else
	UNAME_S := $(shell uname -s)
	INCLUDES := -I../.includes/
	LINK_FLAGS := -L../.libs/
    ifeq ($(UNAME_S),Darwin)
		LIB_FLAGS := -fPIC -dynamiclib -Wno-unused-command-line-argument -pedantic
		TARGET_LIB := libMathEngine.dylib
	else
		LIB_FLAGS := -fPIC -shared
		TARGET_LIB := libMathEngine.so
    endif
endif

CXXFLAGS := ${OPT_FLAG} -std=c++17 ${LIB_FLAGS} -Wall -MMD -Werror=vla ${INCLUDES}
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

ifeq ($(OS),Windows_NT)
	LINK_STEP := ar.exe rcs ${TARGET_LIB} ${OBJECTS}
else
	LINK_STEP := ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${TARGET_LIB} ${LINK_FLAGS} -lgsl -lgslcblas -lm
endif

${TARGET_LIB}: ${OBJECTS}
	${LINK_STEP}


# $(SOURCES:.cc=.d):%.d:%.cc
# 	${CXX} ${CXXFLAGS}  -c $< $@

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
