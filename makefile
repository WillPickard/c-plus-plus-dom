all: test.cpp dom.cpp element.cpp element_collection.cpp storage_engine.cpp
	g++ -std=c++11 -o test test.cpp

run: all
	./test