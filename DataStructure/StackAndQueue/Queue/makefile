queue.out : queue.o main.o
	g++ -o queue.out queue.o main.o

queue.o : queue.cpp
	g++ -std=c++2a -Wall -c queue.cpp

main.o : main.cpp
	g++ -std=c++2a -Wall -c main.cpp

clean :
	rm main.o queue.o queue.out