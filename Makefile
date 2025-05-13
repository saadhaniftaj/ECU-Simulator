CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC = main.cpp ECU.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = ecu_sim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET) 