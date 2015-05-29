CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic

sspapp: sspapp.o graph.o minpriority.o
	$(CXX) -o sspapp sspapp.o graph.o minpriority.o

sspapp.o: sspapp.cpp sspapp.h graph.h

graph.o: graph.cpp graph.h minpriority.h

minpriority.o:	minpriority.cpp minpriority.h

clean:
	rm -f *.o sspapp
