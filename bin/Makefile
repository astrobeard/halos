
CC = gcc 
CFLAGS = -Wsign-conversion -Wsign-compare 
FILES = ../src/*.c ../src/io/*.c ../src/statistics/*.c 

all: dm_dspin.o 
.PHONY: clean 

%.o: %.c 
	$(CC) $(CFLAGS) $(FILES) $< -o $@ 

clean: 
	rm -f *.o 
