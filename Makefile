# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
LIBS = -lsqlite3

# Files
SRC = main.cpp src/Dictionary.cpp src/Database.cpp
TARGET = dict

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)

