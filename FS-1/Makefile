CL = clang++
TARGET = read-file

all: $(TARGET) run

run: $(TARGET)
	./$(TARGET) a.txt

$(TARGET): $(TARGET).o 
	$(CL) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).cpp 
	$(CL) -c $(TARGET).cpp -o $(TARGET).o

clean:
	@echo "cleaning.."
	rm $(TARGET) *.o 
