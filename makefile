all: oth.o main.o
	g++ -Wall -o othello oth.o main.o
oth.o: oth.cpp oth.h
	g++ -Wall -c oth.cpp
main.o: main.cpp oth.h
	g++ -Wall -c main.cpp
