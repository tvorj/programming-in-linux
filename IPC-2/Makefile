CL = clang++
TARGET = prime-calculator

all: $(TARGET) run

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(TARGET).o
	$(CL) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp
	$(CL) -c $(TARGET).cpp -o $(TARGET).o

clean:
	@echo "cleaning..."
	rm $(TARGET) *.o

