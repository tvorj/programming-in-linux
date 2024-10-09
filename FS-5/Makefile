CL = clang++
TARGET = manual-append

all: $(TARGET) run

run: $(TARGET) a.txt
	./$(TARGET) a.txt

a.txt:
	echo "FS-5" > a.txt

$(TARGET): $(TARGET).o
	$(CL) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp
	$(CL) -c $(TARGET).cpp -o $(TARGET).o

clean:
	@echo "cleaning..."
	rm $(TARGET) *.o

