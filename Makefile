# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# SFML libraries to link
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC = Breakout.cpp platform.cpp balls.cpp game.cpp blocks.cpp powerUp.cpp level.cpp startMenu.cpp

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
