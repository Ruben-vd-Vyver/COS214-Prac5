CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g -Iinclude
# Link the C++ runtime statically so the binary also runs on the slim
# runtime image, whose libstdc++ is older than the one in gcc:13.
LDFLAGS := -static-libstdc++ -static-libgcc
SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:src/%.cpp=build/%.o)
TARGET := campusguard

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build $(TARGET)
