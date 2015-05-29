CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS = -lrt

PROG = csort
HDRS = CensusData.h
SRCS = CensusDataSorts.cpp CensusData.cpp CensusSort.cpp
OBJS = $(SRCS:.cpp=.o)

$(PROG) : $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(PROG)

CensusSort.o : CensusSort.cpp CensusData.h
	$(CXX) $(CXXFLAGS) CensusSort.cpp

CensusData.o : CensusData.cpp CensusData.h
	$(CXX) $(CXXFLAGS) CensusData.cpp

CensusDataSorts.o : CensusDataSorts.cpp CensusData.h
	$(CXX) $(CXXFLAGS) CensusDataSorts.cpp

clean :
	rm -f core $(PROG) *.o
