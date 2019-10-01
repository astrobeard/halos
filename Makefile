
all: backend bin 
.PHONY: backend bin clean 

backend: 
	$(MAKE) -C src/ 
	$(MAKE) -C bin/ 

clean: 
	$(MAKE) -C src/ clean 
	$(MAKE) -C bin/ clean 

