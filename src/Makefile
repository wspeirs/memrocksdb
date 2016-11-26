GPP   = /usr/bin/g++
GCC   = /usr/bin/gcc
FLAGS = -W -Wall -std=c++11  -g -O3
INC   = -I ../include
LIBS  =
EXEC  = test

all: text_protocol_parser.o 
	$(GPP) $(FLAGS) $(LIBS) *.o -o $(EXEC)

text_protocol_parser.o: text_protocol_parser.cpp
	$(GPP) -c $(FLAGS) $(INC) text_protocol_parser.cpp

clean:
	rm *~ *.o $(EXEC)
