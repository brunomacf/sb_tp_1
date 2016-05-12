Sources 	= ./src
Builds 		= ./build
Flags 		= -std=c++11

all: clean mkdirs vm.o
	g++ $(Flags) -o tp1 $(Sources)/main.cpp $(Builds)/vm.o

clean:
	rm -rf $(Builds)
	rm -f tp1

vm.o:
	g++ $(Flags) -c $(Sources)/vm.cpp -o $(Builds)/vm.o

mkdirs:
	mkdir $(Builds)
