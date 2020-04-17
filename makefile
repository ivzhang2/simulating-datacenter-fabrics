all: flow.o
	gcc flow.o -o main

flow.o: flow.c flow.h
	gcc -c flow.c

run: main
	./main

clean: 
	rm main *.o