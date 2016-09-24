lab: make_dir lab1

main.o = ./bin/main.o
algorithm.o = ./bin/algorithm.o
io.o = ./bin/io.o
util.o = ./bin/util.o

main.c = ./src/main.c
algorithm.c = ./src/algorithm.c
io.c = ./src/io.c
util.c = ./src/util.c

algorithm.h = ./include/algorithm.h
io.h = ./include/io.h
util.h = ./include/util.h

lab1: $(main.o) $(algorithm.o) $(io.o) $(util.o)
	gcc $(main.o) $(algorithm.o) $(io.o) $(util.o) -o lab1

$(main.o): $(main.c) $(algorithm.h) $(io.h) $(util.h)
	gcc -c $(main.c) -o $(main.o)

$(algorithm.o): $(algorithm.c) $(io.h) $(util.h)
	gcc -c $(algorithm.c) -o $(algorithm.o)

$(io.o): $(io.c)
	gcc -c $(io.c) -o $(io.o)

$(util.o): $(util.c) $(io.h)
	gcc -c $(util.c) -o $(util.o)

make_dir:
	mkdir -p bin

clean:
	rm -r bin