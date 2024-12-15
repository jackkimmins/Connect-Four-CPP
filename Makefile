# This file is used for building the project using the make command.

CXX = g++
CXXFLAGS = -std=c++20 -O3

TARGET = bin/main

# Automatically find all .cpp files in the src directory
SOURCES = $(wildcard src/*.cpp)

# Convert the list of source files to a list of object files
OBJECTS = $(SOURCES:.cpp=.o)

# Use debug flags for development
DEBUGFLAGS = -g -Og -fsanitize=address,undefined

# Check if the src and bin directories exist, create them if not
# Create a main.cpp file inside src if it doesn't exist
dirs_and_files:
	@mkdir -p src bin
	@if [ ! -f src/main.cpp ]; then echo '#include <iostream>\n\nint main()\n{\n\tstd::cout << "Hello, World!" << std::endl;\n\treturn 0;\n}' > src/main.cpp; fi

all: dirs_and_files $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(TARGET)

run: $(TARGET)
	clear
	@./$(TARGET)
	@bash -c 'read -n 1 -s'

makerun: all
	@$(MAKE) run

clean:
	rm -f $(TARGET) $(OBJECTS) src/*.o

.PHONY: all clean run debug dirs_and_files makerun