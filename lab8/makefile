
CC = g++
CFLAGS = -g -std=c++11 -Wall
BIN = Rank_byname Rank_byscores

all: $(BIN)

.cpp: 
	$(CC) $(CFLAGS) -o $* $<

clean:
	rm -f $(BIN) *.o
