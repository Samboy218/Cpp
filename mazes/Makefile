
all: main

main: main.o maze.o mazeNode.o nodeStack.o
	g++ -o main main.o maze.o mazeNode.o nodeStack.o

main.o: main.cpp
	g++ -c -o main.o main.cpp

maze.o: maze.cpp maze.h
	g++ -c -o maze.o maze.cpp

mazeNode.o: mazeNode.cpp mazeNode.h
	g++ -c -o mazeNode.o mazeNode.cpp

nodeStack.o: nodeStack.cpp nodeStack.h
	g++ -c -o nodeStack.o nodeStack.cpp

.PHONY: debug
debug: *.cpp *.h
	g++ -c -o nodeStack.o nodeStack.cpp -g -g -lefence
	g++ -o main main.o maze.o mazeNode.o nodeStack.o -lefence
	g++ -c -o mazeNode.o mazeNode.cpp -g -lefence
	g++ -c -o maze.o maze.cpp -g -lefence
	g++ -c -o main.o main.cpp -g -lefence
	g++ -o main main.o maze.o mazeNode.o nodeStack.o -g -lefence
.PHONY:clean
clean:
	rm -rf *.o
	rm -rf main
