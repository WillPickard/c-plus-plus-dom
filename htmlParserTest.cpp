//html_parser_test
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "html_parser.cpp"

using namespace std;

const char * TEST_FILE = "test.html";


int main(int argc, const char * argv[])
{
	cout << "testing html parser..." << endl;
	ifstream file (TEST_FILE);

	string lines;
	
	lines.assign( (istreambuf_iterator<char> (file) ),
					(istreambuf_iterator<char> ()) );

//	cout << lines << endl;

	HTMLParser * parser = new HTMLParser(lines.c_str());
	cout << "parser contents: " << endl;
	cout << parser->getRawHTML() << endl;
	cout << "---------------------------------------------" << endl << endl << endl;

	//const char * tag1, tag2, tag3;
/*
	vector<char> v1 = parser->nextTag();
	vector<char> v2 = parser->nextTag();
	vector<char> v3 = parser->nextTag();

	string tag1 (v1.begin(), v1.end());
	string tag2 (v2.begin(), v2.end());
	string tag3 (v3.begin(), v3.end());

	//cout << "---------------------------------------------------" << endl;

	cout << "tag1 : " << tag1 << endl << endl;
	cout << "tag2 : " << tag2 << endl << endl;
	cout << "tag3 : " << tag3 << endl << endl;

	cout << "---------------------------------------------------" << endl;

	cout << "tag1 : " << tag1 << endl << endl;
	cout << "tag2 : " << tag2 << endl << endl;
	cout << "tag3 : " << tag3 << endl << endl;
*/
	while(parser->hasMore())
	{
		vector<char> v = parser->next();
		string s (v.begin(), v.end());
		cout << s;
		if(parser->isTag(s))
		{
			cout << " isTag!";
		}
		cout << endl;
	}
	return 0;
}

