all: make_dir main

make_dir:
	mkdir -p bin

main: ./bin/main.o ./bin/matrix.o
	g++ ./bin/main.o ./bin/matrix.o -o main

./bin/main.o: ./src/main.cpp ./include/matrix.h
	g++ -c ./src/main.cpp -o ./bin/main.o

./bin/matrix.o: ./src/matrix.cpp ./include/matrix.h
	g++ -c ./src/matrix.cpp -o ./bin/matrix.o

clean:
	rm -rf bin main