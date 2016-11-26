GPP   = /usr/bin/g++
GCC   = /usr/bin/gcc
FLAGS = -W -Wall -std=c++11 -g -O3
PROG_INC = -I ../include
TEST_INC = $(PROG_INC) -I ../../googletest/googletest/include
LIBS  = ../../googletest/build/googlemock/gtest/libgtest.a -lpthread
EXEC  = memrocksdb

all: memcached_text_protocol_parser_test.o
	$(GPP) ../src/*.o memcached_text_protocol_parser_test.o $(LIBS) -o test

memcached_text_protocol_parser_test.o: memcached_text_protocol_parser_test.cpp
	$(GPP) $(FLAGS) $(TEST_INC) -c memcached_text_protocol_parser_test.cpp

clean:
	rm *~ *.o $(EXEC)
