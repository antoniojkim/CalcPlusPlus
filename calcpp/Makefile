CXX := clang-10

mode := release
optflag.release := -g -Ofast
optflag.debug := -g
OPT_FLAG := ${optflag.${mode}}

LLVM_INCLUDE_FLAGS := $(shell bash -c "llvm-config --includedir")
LLVM_LINK_FLAGS := $(shell bash -c "llvm-config --ldflags --system-libs --libs core")

ifeq ($(OS),Windows_NT)
	INCLUDES := -IC:\DEV\vcpkg\packages\gsl_x64-windows\include
	LIB_FLAGS := -fPIC -static
	LINK_FLAGS := -LC:\DEV\vcpkg\packages\gsl_x64-windows\bin
	LINK_LIB_FLAGS :=
	TARGET_LIB := libcalcpp.a
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		INCLUDES :=
		LINK_FLAGS :=
		LIB_FLAGS := -fPIC  -Wno-unused-command-line-argument -pedantic
		LINK_LIB_FLAGS := -dynamiclib
		TARGET_LIB := libcalcpp.dylib
	else
		INCLUDES := -I../.includes/
		LINK_FLAGS := -L../.libs/
		LIB_FLAGS := -fPIC
		LINK_LIB_FLAGS := -shared ${LLVM_LINK_FLAGS}
		TARGET_LIB := libcalcpp.so
	endif
endif

LLVM_INCLUDE_FLAGS := $(shell bash -c "llvm-config --includedir")
LLVM_LINK_FLAGS := $(shell bash -c "llvm-config --ldflags --system-libs --libs core")

CXXFLAGS := ${OPT_FLAG} -std=c++17 ${LIB_FLAGS} -Wall -MMD -Werror=vla ${INCLUDES} -I${LLVM_INCLUDE_FLAGS}
CPPFLAGS := -DDEBUG

UTILS := $(wildcard calcpp/Utils/*.cc)
# MATHENGINE := $(wildcard MathEngine/*.cc)
SCANNER := $(wildcard calcpp/Scanner/*.cc)
AST := $(wildcard calcpp/AST/*.cc)
PARSER := $(wildcard calcpp/Parser/*.cc)
OPERATORS := $(wildcard calcpp/Operators/*.cc)
# EXPRESSIONS := $(wildcard Expressions/*/*.cc)
# FUNCTIONS := $(wildcard Functions/*.cc)
# FUNCTIONIMPL := $(wildcard Functions/*/*.cc)

SOURCES := ${UTILS} ${SCANNER} ${AST} ${PARSER} ${OPERATORS} # ${EXPRESSIONS} ${FUNCTIONS} ${FUNCTIONIMPL} ${MATHENGINE}
OBJECTS := ${SOURCES:.cc=.o}
DEPENDS := ${OBJECTS:.o=.d}

ifeq ($(OS),Windows_NT)
	LINK_STEP := ar.exe rcs ${TARGET_LIB} ${OBJECTS}
else
	LINK_STEP := ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${TARGET_LIB} ${LINK_FLAGS} -lgsl -lgslcblas -lm ${LINK_LIB_FLAGS} -lstdc++
endif

${TARGET_LIB}: ${OBJECTS}
	${LINK_STEP}

MAIN_SOURCES := main.cc
MAIN_OBJECTS := ${MAIN_SOURCES:.cc=.o}

main: ${TARGET_LIB} ${MAIN_OBJECTS}
	${CXX} ${CXXFLAGS} -o main ${MAIN_OBJECTS} -L. -lcalcpp ${LINK_FLAGS} -lgsl -lgslcblas -lm ${LLVM_LINK_FLAGS} -lstdc++

-include ${DEPENDS}

clean:
	rm -f ${OBJECTS} ${MAIN_OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
