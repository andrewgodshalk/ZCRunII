# Makefile for ZCRunII
# Compiles all programs directly in subfolders.
# Modified: 2016-08-08
# TO DO: ----

all: NtupleProcessor
    make -f NtupleProcessor/Makefile

clean:
    make clean -f NtupleProcessor/Makefile
