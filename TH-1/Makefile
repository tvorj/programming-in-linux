CL = clang++
TARGET = arr_sum

all: $(TARGET) run

run: $(TARGET)
	./$(TARGET) 10 2

$(TARGET): $(TARGET).o
	$(CL) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp
	$(CL) -c $(TARGET).cpp -o $(TARGET).o

clean:
	@echo "cleaning..."
	rm $(TARGET) *.o

