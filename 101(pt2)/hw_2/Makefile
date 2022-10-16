CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = nqueens.o linkedlist.o

nqueens: $(OBJECTS)
	    $(CXX) -g $(CXXFLAGS) -o $@ nqueens.o linkedlist.o

nqueens.o: linkedlist.h nqueens.cpp
		$(CXX) -g $(CXXFLAGS) -c nqueens.cpp

#utils.o: utils.cpp utils.h
#		$(CXX) -g $(CXXFLAGS) -c utils.cpp

clean:
	rm *.o
	rm nqueens

