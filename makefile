all: Node.o BTree.o main.o
	g++ *.o -o main

%.o: %.cpp %.h
	$(CC) $< -c -o $@

clean:
	rm -rf *.o main
