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

simple-copy: main.cpp SimpleCopy.hpp ReadContent.hpp
	$(CL) main.cpp -o simple-copy

clean:
	@echo "cleaning..."
	rm simple-copy *.txt
