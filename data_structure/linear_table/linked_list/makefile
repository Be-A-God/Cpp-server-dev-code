singly_linked_list.out : main.o
	g++ -o singly_linked_list.out main.o

main.o : main.cpp
	g++ -c -std=c++2a -fconcepts -Wall main.cpp

clean :
	rm main.o singly_linked_list.out