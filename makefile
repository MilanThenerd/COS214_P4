CXX = g++
CXXFLAGS = -Wall -std=c++17

TARGET = Game
SOURCES = $(wildcard *.cpp) # Use wildcard to gather .cpp files
OBJECTS = $(SOURCES:.cpp=.o)

LIBS = # Define any common libraries here (e.g., -lm)

# Default target: build without GUI
all: build-without-gui

# Build without GUI
build-without-gui: $(TARGET)

# Build with GUI (SFML)
build-with-gui: CXXFLAGS += -DUSE_GUI
build-with-gui: LIBS += -lsfml-graphics -lsfml-window -lsfml-system
build-with-gui: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Compile each source file into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the game without GUI
run: clean build-without-gui
	./$(TARGET)

# Run the game with GUI (SFML)
demo: clean build-with-gui
	./$(TARGET)

.PHONY: all clean run demo
