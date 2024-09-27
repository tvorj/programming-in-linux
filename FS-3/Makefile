CL = clang++

all: hacker-rm print 

print: a.txt
	ls
	./hacker-rm a.txt
	ls

a.txt:
	touch a.txt 

hacker-rm: main.cpp HackerRm.hpp
	$(CL) main.cpp -o hacker-rm

clean:
	@echo "cleaning..."
	rm hacker-rm  
