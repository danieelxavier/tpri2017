### C++ Arguments
CC=g++
CF=-std=c++11 -Wall

### Program Arguments
NAME=main

### Compiler Arguments
# SRC_P=src

all: merge clean

merge:	document.o query.o parser.o main.o
	$(CC) $(CF) -o $(NAME) document.o query.o parser.o main.o

main.o: document.o query.o parser.o main.cpp
	$(CC) $(CF) -c main.cpp

parser.o: document.o query.o parser.cpp parser.hpp
	$(CC) $(CF) -c parser.cpp

document.o: query.cpp query.hpp
	$(CC) $(CF) -c query.cpp

document.o: document.cpp document.hpp
	$(CC) $(CF) -c document.cpp



clean:
	rm -rf *.o