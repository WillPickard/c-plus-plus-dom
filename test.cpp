//test.cpp
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "dom.cpp"
#include "element.cpp"
#include "element_collection.cpp"
#include "storage_engine.cpp"

using namespace std;

const char * TEST_FILE = "reddit.html";

int main(int argc, const char * argv[])
{
	ifstream file (TEST_FILE);

	string lines;
	string line;
	while(getline(file, line))
	{
		lines += line;
	}

	DOM * dom = new DOM(lines);

	return 0;
}