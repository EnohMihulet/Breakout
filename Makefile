# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# SFML libraries to link
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC = cppFiles/Breakout.cpp cppFiles/platform.cpp cppFiles/balls.cpp cppFiles/game.cpp cppFiles/blocks.cpp cppFiles/powerUp.cpp cppFiles/level.cpp cppFiles/startMenu.cpp

# Output executable
TARGET = Breakout

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# Clean rule
clean:
	rm -f $(TARGET)
