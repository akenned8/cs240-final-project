CFLAGS = -Wall -Wextra -pedantic -DDEBUG -g -std=c++14 -march=native
P = program3
A = Planet
B = Galaxy

all: $(P)

$(P): $(B).o $(A).o $(P).o
	g++ $(CFLAGS) -O3 $(P).o $(A).o $(B).o -o $(P)

$(P).o: $(P).cpp
	g++ -c -O3 -march=native $(P).cpp -o $(P).o

$(A).o: $(A).cpp $(A).h
	g++ -c -O3 -march=native $(A).cpp -o $(A).o

$(B).o: $(B).cpp $(B).h
	g++ -c -O3 -march=native $(B).cpp -o $(B).o

run: all
	./$(P)

memcheck: all
	valgrind --track-origins=yes -v --leak-check=full --show-leak-kinds=all ./$(P)

clean:
	rm $(P) *.o