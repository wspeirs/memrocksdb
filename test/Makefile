GPP   = /usr/bin/g++
GCC   = /usr/bin/gcc
FLAGS = -W -Wall -std=c++11 -g -O3
PROG_INC = -I ../include
TEST_INC = $(PROG_INC) -I ../../googletest/googletest/include
LIBS  = ../../googletest/build/googlemock/gtest/libgtest.a -lpthread
EXEC  = memrocksdb

all: text_protocol_parser_test.o
	$(GPP) ../src/*.o text_protocol_parser_test.o $(LIBS) -o test

text_protocol_parser_test.o: text_protocol_parser_test.cpp
	$(GPP) $(FLAGS) $(TEST_INC) -c text_protocol_parser_test.cpp

clean:
	rm *~ *.o $(EXEC)
