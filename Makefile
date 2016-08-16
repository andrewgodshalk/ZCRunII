# Makefile for ZCRunII
# Compiles all programs directly in subfolders.
# Modified: 2016-08-08
# TO DO: ----

all: NtupleProcessor
	make -C NtupleProcessor

clean:
	make clean -C NtupleProcessor
