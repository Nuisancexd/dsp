CC = g++
FLAGS = -m32 -O3 -std=c++20 -fsanitize=address -pthread -Iinclude
SRC = src/main.cpp src/complex.cpp src/signal.cpp src/time_domain.cpp

OBJ = $(SRC:.cpp=.o)
EXEC = dsplib

all: $(EXEC)

$(EXEC): $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
		$(CC) $(FLAGS) -c $< -o $@

clean:
		rm -f $(OBJ) $(EXEC)