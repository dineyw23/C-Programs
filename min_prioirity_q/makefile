CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic

minpq: minpriority.o main.o
	$(CXX) -o minpq	main.o minpriority.o

minpriority.o : minpriority.cpp minpriority.h
	$(CXX)	$(CXXFLAGS)	minpriority.cpp

main.o: main.cpp minpriority.h
	$(CXX) $(CXXFLAGS) main.cpp
clean :
	rm -f core $(PROG) *.o
