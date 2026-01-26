# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
LIBS = -lsqlite3

# Executable name
TARGET = dict

# Source files
SRCS = main.cpp \
       src/Dictionary.cpp \
       src/Trie.cpp \
	   src/SpellChecker.cpp \
       src/Database.cpp

# Object files (auto-generated from SRCS)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Compile step (this is the magic)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)

