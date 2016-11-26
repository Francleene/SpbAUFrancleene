flags = -Wall -Werror

all: make_dir main

make_dir:
	mkdir -p bin

main: ./bin/main.o ./bin/matrix.o
	g++ $(flags) ./bin/main.o ./bin/matrix.o -o main

./bin/main.o: ./src/main.cpp ./include/matrix.h
	g++ $(flags) -c ./src/main.cpp -o ./bin/main.o

./bin/matrix.o: ./src/matrix.cpp ./include/matrix.h
	g++ $(flags) -c ./src/matrix.cpp -o ./bin/matrix.o

clean:
	rm -rf bin main