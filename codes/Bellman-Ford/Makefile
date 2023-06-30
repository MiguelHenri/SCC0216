CC = g++
CFLAGS = -Wall

all: main

main: graph.o trab4.cpp
	$(CC) trab4.cpp -o main.exe $(CFLAGS) graph.o

graph.o: Graph.cpp
	$(CC) -c Graph.cpp -o ./graph.o $(CFLAGS)

zip:
	zip ex.zip *.cpp *.h Makefile

clean:
	rm *.o *.exe

run:
	./main.exe