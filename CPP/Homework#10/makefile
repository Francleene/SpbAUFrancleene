flags = -Wall -Werror

all: make_dir main

make_dir:
	mkdir -p bin

main: ./bin/figure.o ./bin/circle.o ./bin/rectangle.o ./bin/scheme.o ./bin/main.o 
	g++ ./bin/figure.o ./bin/circle.o ./bin/rectangle.o ./bin/scheme.o ./bin/main.o -o main

./bin/main.o: ./src/main.cpp ./include/scheme.h
	g++ $(flags) -c ./src/main.cpp -o ./bin/main.o

./bin/scheme.o: ./src/scheme.cpp ./include/scheme.h ./include/figure.h ./include/circle.h ./include/rectangle.h
	g++ $(flags) -c ./src/scheme.cpp -o ./bin/scheme.o

./bin/circle.o: ./src/circle.cpp ./include/circle.h ./include/figure.h
	g++ $(flags) -c ./src/circle.cpp -o ./bin/circle.o

./bin/rectangle.o: ./src/rectangle.cpp ./include/rectangle.h ./include/figure.h
	g++ $(flags) -c ./src/rectangle.cpp -o ./bin/rectangle.o

./bin/figure.o: ./src/figure.cpp ./include/figure.h
	g++ $(flags) -c ./src/figure.cpp -o ./bin/figure.o

clean:
	rm -rf bin main
