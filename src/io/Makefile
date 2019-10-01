
CC = gcc 
CFLAGS = -c -fPIC 

all: input.o 
.PHONY: clean 

%.o: %.c *.h 
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 
