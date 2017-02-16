FLAGS = -std=c++11 -Wall

all: make_dir empl_db

make_dir:
	mkdir -p bin

empl_db: bin/main.o bin/employees.o bin/interface.o
	g++ $(FLAGS) bin/main.o bin/employees.o bin/interface.o -o empl_db

bin/main.o: src/main.cpp include/employees.hpp include/interface.hpp
	g++ $(FLAGS) -c src/main.cpp -o bin/main.o

bin/employees.o: src/employees.cpp include/employees.hpp
	g++ $(FLAGS) -c src/employees.cpp -o bin/employees.o

bin/interface.o: src/interface.cpp include/interface.hpp
	g++ $(FLAGS) -c src/interface.cpp -o bin/interface.o

clean:
	rm -rf bin empl_db