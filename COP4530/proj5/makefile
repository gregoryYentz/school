all: proj5.x

proj5.x: passserver.o proj5.o
	g++ -std=c++11 -o proj5.x proj5.o passserver.o -lcrypt

passserver.o: passserver.h passserver.cpp hashtable.h hashtable.hpp
	g++ -std=c++11 -c passserver.cpp

proj5.o: passserver.h hashtable.h proj5.cpp
	g++ -std=c++11 -c proj5.cpp

clean:
	rm *.o
	rm *.x
