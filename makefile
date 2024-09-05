CXX = g++
CXXFLAGS = -Wall -std=c++17

TARGET = Game
OBJECTS = $(SOURCES:.cpp=.o)

SOURCES = *.cpp

all: build-without-gui

build-without-gui: $(TARGET)

build-with-gui: CXXFLAGS += -DUSE_GUI -lsfml-graphics -lsfml-window -lsfml-system
build-with-gui: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: clean build-without-gui
	./Game

demo: clean build-with-gui
	./Game

.PHONY: all clean