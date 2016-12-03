make: make_dir pqsort

make_dir:
	mkdir -p bin

pqsort: ./bin/main.o ./bin/thread_pool.o
	gcc ./bin/main.o ./bin/thread_pool.o -o pqsort -lpthread

./bin/main.o: ./src/main.c ./include/thread_pool.h
	gcc -c ./src/main.c -o ./bin/main.o -lpthread

./bin/thread_pool.o: ./src/thread_pool.c ./include/thread_pool.h
	gcc -c ./src/thread_pool.c -o ./bin/thread_pool.o -lpthread

clean:
	rm -rf bin pqsort