all: simulation.o flow.o arrival.o
	gcc simulation.o flow.o arrival.o -o simulation

flow.o: flow.c flow.h
	gcc -c flow.c

arrival.o: arrival.c arrival.h
	gcc -c arrival.c

simulation.o: simulation.c arrival.h flow.h
	gcc -c simulation.c

run: simulation
	./simulation

clean: 
	rm simulation *.o *.gch