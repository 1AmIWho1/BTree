all: Node.o BTree.o main.o
	g++ *.o -o main -lm -lSDL2 -g -fsanitize=address

%.o: %.cpp %.h
	$(CC) $< -c -o $@

clean:
	rm -rf *.o main
