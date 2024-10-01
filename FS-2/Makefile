CL = clang++
TARGET = simple-copy

all: $(TARGET) run

run: $(TARGET) a.txt b.txt	
	./$(TARGET) a.txt b.txt

b.txt:
	echo "its b" > b.txt

$(TARGET): $(TARGET).o 
	$(CL) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp 
	$(CL) -c $(TARGET).cpp -o $(TARGET).o

clean:
	@echo "cleaning..."
	rm $(TARGET) *.o
