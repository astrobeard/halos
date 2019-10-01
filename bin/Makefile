
CC = gcc 
FILES = ../src/*.c ../src/io/*.c 

all: dm_dspin.o 
.PHONY: clean 

%.o: %.c 
	$(CC) $(FILES) $< -o $@ 

clean: 
	rm -f *.o 
