CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -O2 -Iinclude
TARGET = describe_object
TEST_TARGET = test_objects
SOURCES = src/main.cpp
TEST_SOURCES = tests/test_main.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SOURCES)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all test clean

