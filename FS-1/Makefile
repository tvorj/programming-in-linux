CL = clang++

all: read-only print

print: read-only
	cat a.txt
	./read-only a.txt

read-only: main.o ReadFile.o
	$(CL) main.o ReadFile.o -o read-only

main.o: main.cpp ReadFile.hpp
	$(CL) -c main.cpp -o main.o

ReadFile.o: ReadFile.cpp ReadFile.hpp
	$(CL) -c ReadFile.cpp -o ReadFile.o

clean:
	@echo "cleaning.."
	rm read-only *.o 
