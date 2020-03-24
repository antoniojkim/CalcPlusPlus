CXX = g++
CXXFLAGS = -Ofast -std=c++17 -Wall -MMD -Werror=vla $(shell gsl-config --cflags)
EXEC = experiment

OBJECTS = timing_experiment.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} $(shell gsl-config --libs) -o ${EXEC} -L../../MathEngine -lMathEngine

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
