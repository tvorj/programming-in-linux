CL = clang++
TARGET = hacker-rm

all: $(TARGET) run 

run: a.txt
	./$(TARGET) a.txt

a.txt:
	echo "content of a" >  a.txt 

$(TARGET): $(TARGET).o
	$(CL) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp 
	$(CL) -c $(TARGET).cpp -o $(TARGET).o

clean:
	@echo "cleaning..."
	rm $(TARGET) *.o
