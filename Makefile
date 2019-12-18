CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall -MMD -Werror=vla $(shell gsl-config --cflags)
EXEC = calc

OBJECTS = Parser/Scanner/scanner.o Parser/Parser/parsetree.o Parser/Parser/parser.o calc.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} $(shell gsl-config --libs) -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
