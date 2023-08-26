CXX = g++
CF = -Wall -pedantic -Wextra 
CFD = $(CF) -g -fsanitize=address
LF = -ltinfo
LFD = $(LF) -fsanitize=address 

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(OBJ)
	$(CXX) $(OBJ) $(LFD) -o a.out

src/%.o: src/%.cpp
	$(CXX) $< $(CFD) -c -o $@

clean:
	rm -f $(OBJ) a.out
