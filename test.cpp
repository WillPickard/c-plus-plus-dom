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

const char * TEST_FILE = "test2.html";

int main(int argc, const char * argv[])
{
	ifstream file (TEST_FILE);

	string lines;

	lines.assign( (istreambuf_iterator<char> (file) ),
					(istreambuf_iterator<char> ()) );

	//cout << lines << endl;
	DOM * dom = new DOM(lines);

	cout << "done" << endl;
	return 0;
}