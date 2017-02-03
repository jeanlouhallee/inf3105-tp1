tp1: tp1.o
	g++ -o exe tp1.cpp
	rm *.o
	clear
tp1.o: tp1.cpp
	g++ -c tp1.cpp
