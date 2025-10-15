CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

JSON_INC = include 

TARGET = game

SRCS = $(wildcard *.cpp) $(wildcard Network/*.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(JSON_INC) -o $@ $^


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(JSON_INC) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

train: $(TARGET)
	./$(TARGET) train

play: $(TARGET)
	./$(TARGET) play

.PHONY: all clean rebuild run