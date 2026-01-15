CXX      := g++
CXXFLAGS := -std=c++20 -O3 -march=native -Wall -Wextra -Wpedantic
LDFLAGS  :=
TARGET   := main
SRC      := main.cpp
DEPS     := math.hpp shaders.hpp

.PHONY: all run clean open rebuild

all: $(TARGET)

$(TARGET): $(SRC) $(DEPS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TArget)

open:
	./open.sh

rebuild: clean all
