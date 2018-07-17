##############################################################################################
# Author: Yassine Maalej, UIDAHO
# email: maalej.yessine@gmail.com || maal4948@vandals.uidaho.edu
# Makefile for Logger class and example of using it.
# Date: December 4, 2017
##############################################################################################

# program name
PROGNAME= MAIN_LOGGER_RIGHTWARE

#Compiler g++- 4.9 for my case
CXX=g++

# Additional Flags
CXXFLAGS += -g -Wall -std=c++11 -pthread


# CPP source files
SRCS=\
main.cpp\
logger.cpp\

# Header files
HDRS=\
logger.hpp

# Object files
OBJS = $(SRCS:.c=.o)

# all files
ALLFILES=$(HDRS) $(SRCS) Makefile


main:	$(SRCS)
		$(CXX) $(CXXFLAGS) -o $(PROGNAME) $(SRCS)

core:	main.o
		$(CXX) $(CXXFLAGS) -o $(PROGNAME) main.o

debug:
		gdb $(PROGNAME) core

all:
		touch  $(HDRS) $(SRCS)
		make

size:$(HDRS) $(SRCS)
	wc $?

srcs:	$(HDRS)  $(SRCS)
	echo $(HDRS)  $(SRCS)

allfiles: $(ALLFILES)
	echo $(ALLFILES)

clean:
	rm -f *.o *.exe core

#Make a backup file
backup: $(ALLFILES)
		mkdir -p Backup
		cp $(ALLFILES) Backup
