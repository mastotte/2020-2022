CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = bard.o linkedlist.o

bard: $(OBJECTS)
	    $(CXX) -g $(CXXFLAGS) -o $@ bard.o linkedlist.o

bard.o: linkedlist.h bard.cpp
		$(CXX) -g $(CXXFLAGS) -c bard.cpp

#utils.o: utils.cpp utils.h
#		$(CXX) -g $(CXXFLAGS) -c utils.cpp

clean:
	rm *.o
	rm bard
