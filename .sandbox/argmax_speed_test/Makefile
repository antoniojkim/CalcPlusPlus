CXX = g++
CXXFLAGS = -Ofast -std=c++17 -Wall -MMD -Werror=vla -DDEBUG -I../../.includes/
EXEC = sandbox

OBJECTS =  sandbox.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -L../../.libs/ -lgsl -lgslcblas -lm

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
