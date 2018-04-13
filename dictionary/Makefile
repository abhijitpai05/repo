CC = g++
CFLAGS = -g -Wall -std=c++11

default: dictionary

dictionary: main.o dictionary.o
	$(CC) $(CFLAGS) -o dictionary main.o dictionary.o

main.o: main.cpp trie.hpp
	$(CC) $(CFLAGS) -c main.cpp

dictionary.o: dictionary.cpp dictionary.hpp trie.hpp
	$(CC) $(CFLAGS) -c dictionary.cpp

clean:
	$(RM) dictionary *.o *~