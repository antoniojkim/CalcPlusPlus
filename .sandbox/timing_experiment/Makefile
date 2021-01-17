CXX = g++
CXXFLAGS = -Ofast -std=c++17 -Wall -MMD -Werror=vla -I../../.includes/
EXEC = sandbox

OBJECTS = timing_experiment.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L../../.libs/ -lgsl -lgslcblas -lm -L../../MathEngine -lMathEngine

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
