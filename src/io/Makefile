
CC = gcc 
CFLAGS = -c -fPIC -Wsign-conversion -Wsign-compare 

all: input.o 
.PHONY: clean 

%.o: %.c *.h 
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 
