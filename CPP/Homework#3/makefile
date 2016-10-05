all: make_dir pose_db

pose_db: ./bin/clist.o ./bin/main.o
	gcc -g ./bin/clist.o ./bin/main.o 

./bin/clist.o: ./src/clist.c
	gcc -c ./src/clist.c -o ./bin/clist.o

./bin/main.o: ./src/main.c ./include/clist.h
	gcc -c ./src/main.c -o ./bin/main.o

make_dir: 
	mkdir -p bin

clean:
	rm ./bin/*.o