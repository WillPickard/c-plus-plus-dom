all: test.cpp dom.cpp element.cpp element_collection.cpp storage_engine.cpp
	g++ -std=c++11 -o test test.cpp 

html_parser: htmlParserTest.cpp html_parser.cpp
	g++ -o html_test htmlParserTest.cpp

run: all
	./test

run_html: html_parser
	./html_test