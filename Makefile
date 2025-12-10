# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Target executable
TARGET = spellchecker

# Object files
OBJS = main.o Dictionary.o

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile Dictionary.cpp into Dictionary.o
Dictionary.o: Dictionary.cpp Dictionary.h
	$(CXX) $(CXXFLAGS) -c Dictionary.cpp

# Compile main.cpp into main.o
main.o: main.cpp Dictionary.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
