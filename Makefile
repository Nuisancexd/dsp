CC = g++
FLAGS = -O3 -std=c++20 -fsanitize=address -pthread -Iinclude 
LDFLAGS = -lmatplot -lnodesoup -lfftw3f
vpath %.cpp src
SRC = main.cpp complex.cpp signal.cpp time_domain.cpp freq_domain.cpp plot.cpp

OBJ = $(SRC:.cpp=.o)
EXEC = dsplib

all: $(EXEC)

$(EXEC): $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
		$(CC) $(FLAGS) -c $< -o $@

clean:
		rm -f $(OBJ) $(EXEC)