sequence_table.out :  main.o
	g++ -o sequence_table.out main.o

main.o : main.cpp
	g++ -c -std=c++2a -fconcepts -Wall main.cpp

clean :
	rm main.o sequence_table.out
