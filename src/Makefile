
CC = gcc 
CFLAGS = -c -fPIC 

all: subs catalogue.o halo.o  
.PHONY: clean subs 

%.o: %.c *.h 
	$(CC) $(CFLAGS) $< -o $@ 

subs: 
	$(MAKE) -C io/ 

clean: 
	rm -f *.o 
	$(MAKE) -C io/ clean 

