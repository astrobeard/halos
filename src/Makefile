
CC = gcc 
CFLAGS = -c -fPIC -Wsign-conversion -Wsign-compare 

all: subs catalogue.o halo.o  
.PHONY: clean subs 

%.o: %.c *.h 
	$(CC) $(CFLAGS) $< -o $@ 

subs: 
	$(MAKE) -C io/ 

clean: 
	rm -f *.o 
	$(MAKE) -C io/ clean 

