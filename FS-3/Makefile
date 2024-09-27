CL = clang++

all: hacker-rm print 

print: a.txt
	ls *.txt
	./hacker-rm a.txt
	ls *.txt

a.txt:
	touch a.txt 

hacker-rm: main.o HackerRm.o
	$(CL) main.o HackerRm.o -o hacker-rm

main.o: main.cpp HackerRm.hpp
	$(CL) -c main.cpp -o main.o

HackerRm.o: HackerRm.cpp HackerRm.hpp
	$(CL) -c HackerRm.cpp -o HackerRm.o

clean:
	@echo "cleaning..."
	rm hacker-rm *.o
