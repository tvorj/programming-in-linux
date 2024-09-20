CL = clang++ 

all: result main.o ComplexNumber.o Algo.o print

print: result
	./result

result: main.o ComplexNumber.o Algo.o
	$(CL)  main.o ComplexNumber.o Algo.o -o result

main.o: main.cpp
	$(CL) -c main.cpp -o main.o

ComplexNumber.o: ComplexNumber.cpp
	$(CL) -c ComplexNumber.cpp -o ComplexNumber.o

Algo.o: Algo.cpp
	$(CL) -c Algo.cpp -o Algo.o

clean: 
	@echo "deleting object files"
	rm result *.o
