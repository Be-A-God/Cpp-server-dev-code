SequenList.out :  MySequenList.o
	g++ -o SequenList.out MySequenList.o

MySequenList.o : MySequenList.cpp
	g++ -c -std=c++2a -fconcepts -Wall MySequenList.cpp

clean :
	rm MySequenList.o SequenList.out