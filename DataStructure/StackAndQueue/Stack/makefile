stack.out : stack.o main.o
	g++ -o stack.out stack.o main.o

stack.o : stack.cpp
	g++ -std=c++2a -Wall -c stack.cpp

main.o : main.cpp
	g++ -std=c++2a -Wall -c main.cpp

clean :
	rm main.o stack.o stack.out