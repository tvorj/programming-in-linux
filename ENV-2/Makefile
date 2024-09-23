CL = clang++ 
sort = sortByAbsValue.o

all: result main.o ComplexNumber.o $(sort) print

print: result
	./result

result: main.o ComplexNumber.o $(sort)
	$(CL)  main.o ComplexNumber.o $(sort) -o result

main.o: main.cpp
	$(CL) -c main.cpp -o main.o

ComplexNumber.o: ComplexNumber.cpp
	$(CL) -c ComplexNumber.cpp -o ComplexNumber.o

$(sort): sortByAbsValue.cpp
	$(CL) -c sortByAbsValue.cpp -o $(sort)

clean: 
	@echo "deleting object files"
	rm result *.o
