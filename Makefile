# Makefile for ZCRunII
# Compiles all programs directly in subfolders.
# Modified: 2016-10-24
# TO DO: ----

LOGDIR := logs

all: NtupleProcessor
	@mkdir -p $(LOGDIR)
	make -C NtupleProcessor

clean:
	make clean -C NtupleProcessor
