CC=g++
CFLAGS=-Wall -g -std=c++11

all: median1 median2 filter

median1: median1.cc
	$(CC) $(CFLAGS) -o $@ $^

median2: median2.cc
	$(CC) $(CFLAGS) -o $@ $^

filter: filter.cc
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *~ *.o

clean-all: clean
	rm -rf median1 median2 filter

