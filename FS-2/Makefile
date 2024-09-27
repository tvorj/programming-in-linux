CL = clang++

all: simple-copy print

a.txt:
	touch a.txt
	@echo "content of a.txt" >> a.txt

b.txt:
	touch b.txt
	@echo "content of b.txt" >> b.txt

print: simple-copy a.txt b.txt
	cat a.txt b.txt
	./simple-copy a.txt b.txt
	cat a.txt b.txt

simple-copy: main.o SimpleCopy.o ReadContent.o
	$(CL) main.o ReadContent.o SimpleCopy.o -o simple-copy

main.o: main.cpp SimpleCopy.hpp ReadContent.hpp
	$(CL) -c main.cpp -o main.o

SimpleCopy.o: SimpleCopy.cpp SimpleCopy.hpp ReadContent.hpp
	$(CL) -c SimpleCopy.cpp -o SimpleCopy.o

ReadContent.o: ReadContent.cpp ReadContent.hpp
	$(CL) -c ReadContent.cpp -o ReadContent.o

clean:
	@echo "cleaning..."
	rm simple-copy *.txt *.o
