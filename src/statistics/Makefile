
CC = gcc 
CFLAGS = -c -fPIC -Wsign-conversion -Wsign-compare 

all: utils.o 
.PHONY: clean 

%.o: %.c *.h 
	$(CC) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o 

