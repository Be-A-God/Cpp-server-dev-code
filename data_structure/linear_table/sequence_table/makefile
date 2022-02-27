sequence_table.out :  main_sequence_table.o
	g++ -o sequence_table.out main_sequence_table.o

main_sequence_table.o : main_sequence_table.cpp
	g++ -c -std=c++2a -fconcepts -Wall main_sequence_table.cpp

clean :
	rm main_sequence_table.o sequence_table.out
