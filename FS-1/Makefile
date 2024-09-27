CL = clang++

all: read-only print

print: read-only
	cat a.txt
	./read-only a.txt

read-only: main.cpp ReadFile.hpp
	$(CL) main.cpp -o read-only

clean:
	@echo "cleaning.."
	rm read-only
