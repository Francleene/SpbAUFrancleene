flags=-std=c99 -Wall -Werror

all: make_dir main

make_dir:
	mkdir -p bin

main: ./bin/main.o ./bin/bmp.o
	gcc $(flags) ./bin/main.o ./bin/bmp.o -o main

./bin/main.o: ./src/main.c ./include/bmp.h
	gcc $(flags) -c ./src/main.c -o ./bin/main.o

./bin/bmp.o: ./src/bmp.c ./include/bmp.h
	gcc $(flags) -c ./src/bmp.c -o ./bin/bmp.o

clean:
	rm -rf bin main