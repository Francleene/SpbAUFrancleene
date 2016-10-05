all: make_dir ms_cli

ms_cli: ./bin/ms_cli.o ./bin/mergesort.o
	gcc -g ./bin/ms_cli.o ./bin/mergesort.o -o ms_cli

./bin/ms_cli.o: ./src/ms_cli.c ./include/mergesort.h
	gcc -c ./src/ms_cli.c -o ./bin/ms_cli.o

./bin/mergesort.o: ./src/mergesort.c
	gcc -c ./src/mergesort.c -o ./bin/mergesort.o

make_dir: 
	mkdir -p bin

clean:
	rm ./bin/*.o