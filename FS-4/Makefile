CL = clang++
TARGET = redirect-cin

all: $(TARGET) run

run: $(TARGET) a.txt
	./$(TARGET) a.txt

a.txt:
	echo "FS-4" > a.txt

$(TARGET): $(TARGET).o
	$(CL) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp
	$(CL) -c $(TARGET).cpp -o $(TARGET).o

clean:
	@echo "cleaning..."
	rm $(TARGET) *.o
