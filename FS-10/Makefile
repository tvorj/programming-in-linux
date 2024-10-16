CL = clang++
TARGET = copy-with-holes

all: $(TARGET) run

run: $(TARGET) a.txt
	./$(TARGET) a.txt b.txt

$(TARGET): $(TARGET).o
	$(CL) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp
	$(CL) -c $(TARGET).cpp -o $(TARGET).o

clean:
	@echo "cleaning..."
	rm $(TARGET) *.o

