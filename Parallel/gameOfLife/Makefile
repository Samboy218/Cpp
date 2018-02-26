modName = gameOfLife
sourceName = $(modName).cpp
cc = mpic++


all: $(modName)
    
$(modName): $(sourceName) 
	 $(cc) -O2 -s -DNDEBUG -o $(modName) $(sourceName) 

.PHONY: super
super: $(sourceName) 
	 $(cc) -O3 -s -DNDEBUG -o $(modName) $(sourceName)

.PHONY: clean
clean:
	rm -f $(modName)

.PHONY: debug
debug: $(sourceName) vroot.h
	 $(cc) -o $(modName) $(sourceName) -pg
