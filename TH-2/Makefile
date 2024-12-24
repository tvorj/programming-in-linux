CL = clang++

all: result run

run: result
	./result

result: main.o TH-2.o
	$(CL) main.o TH-2.o -o result

main.o: main.cpp TH-2.h
	$(CL) -c main.cpp -o main.o

TH-2.o: TH-2.cpp TH-2.h
	$(CL) -c TH-2.cpp -o TH-2.o

clear:
	rm *.o result
