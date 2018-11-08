CXX	:=	g++ -std=c++11 -g

String: String.o main.o
	$(CXX) String.o main.o -o String

String.o: String.cc String.hh
	$(CXX) -c String.cc

main.o: String.hh main.cc
	$(CXX) -c main.cc
