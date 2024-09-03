# Define the C++ compiler to use
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# The binary name
TARGET = Game

# List of source files
SOURCES = $(wildcard *.cpp)

# The object files
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: all
	./Game

valgrind: 
