all: make_dir main

main: ./bin/main.o ./bin/clist.o ./bin/position.o
	gcc ./bin/main.o ./bin/clist.o ./bin/position.o -o main

./bin/main.o: ./src/main.c ./include/clist.h ./include/position.h
	gcc -c ./src/main.c -o ./bin/main.o

./bin/clist.o: ./src/clist.c ./include/clist.h 
	gcc -c ./src/clist.c -o ./bin/clist.o

./bin/position.o: ./src/position.c ./include/position.h
	gcc -c ./src/position.c -o ./bin/position.o

make_dir: 
	mkdir -p bin

clean:
	rm ./bin/*.o