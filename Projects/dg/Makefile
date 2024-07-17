CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = stats.o

stats: $(OBJECTS)
	    $(CXX) -g $(CXXFLAGS) -o $@ stats.o

stats.o: stats.cpp
		$(CXX) -g $(CXXFLAGS) -c stats.cpp
