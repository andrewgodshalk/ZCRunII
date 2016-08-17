# Makefile for ZCRunII/NtupleProcessor executable
# Last modified 2016-08-08
# Copied from http://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/
# TO DO: Figure out a good way to add dependancies to utility classes.

CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/NtupleProcessor.exe

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
ROOTFLAGS=`root-config --cflags --glibs`
LIB := -lboost_program_options
CFLAGS := -g -Wall $(ROOTFLAGS)
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB) $(ROOTFLAGS)"; $(CC) $^ -o $(TARGET) $(LIB) $(ROOTFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
