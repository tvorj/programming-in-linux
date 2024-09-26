CL = clang++

all: simple-copy print

print: simple-copy
	cat a.txt b.txt && ./simple-copy a.txt b.txt && cat a.txt b.txt

simple-copy: main.cpp SimpleCopy.hpp ReadContent.hpp
	$(CL) main.cpp -o simple-copy

clean:
	@echo "cleaning..."
	rm simple-copy
