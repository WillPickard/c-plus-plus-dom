//html_parser.cpp

#include "html_parser.h"
#include <iostream> //testing
#include <unistd.h> //testing
HTMLParser::HTMLParser(const std::string raw)
{
	HTMLParser(raw.c_str());
}

HTMLParser::HTMLParser(const char * raw):
	raw_html(raw),
	_i(0)
	{
		raw_html_len = strlen(raw);
	};

const char * HTMLParser::getRawHTML() const
{
	return raw_html;
}

int HTMLParser::getCurrentIndex() const
{
	return _i;
}

int HTMLParser::getRawHTMLLength() const
{
	return raw_html_len;
}

void HTMLParser::setRawHTML(const char * s)
{
	raw_html = s;
}

void HTMLParser::setCurrentIndex(int i)
{
	_i = i;
}

void HTMLParser::setRawHTMLLength(int l)
{
	raw_html_len = l;
}

bool HTMLParser::hasMore() const
{
	if(getCurrentIndex() == getRawHTMLLength())
	{
		return false;
	}

	return true;
}

//pop the prevIndices distance times or until it is empty, setting the currentindex
void HTMLParser::rewind(int distance = 1)
{
	int times = 0;
	int index = _i;
	for(times; times < distance; times++)
	{
		if(prevIndices.empty())
		{
			//can't pop it
			break;
		}
		//push onto forwardIndices so fastword will work
		forwardIndices.push(index);
		index = prevIndices.top();
		prevIndices.pop();
	}
	setCurrentIndex(index);
}

void HTMLParser::fastforward(int distance = 1)
{
	int times = 0;
	int index = _i;
	for(times; times < distance; times++)
	{
		if(forwardIndices.empty())
		{
			//can't pop it
			break;
		}
		//push onto prevIndices so rewind will work
		prevIndices.push(index);
		index = forwardIndices.top();
		forwardIndices.pop();
	}

	setCurrentIndex(index);
}
//use the _i member variable as an index
//return either an open or a close tag
std::vector<char> HTMLParser::nextTag()
{
	prevIndices.push(_i);

	int len = getRawHTMLLength();
	int i = _i; //index for the first tag
	int j = _i; //index for the last tag
	int tagLength = 0; //length of the return tag
	std::vector<char> buf;
	//memset(buf, '\0', sizeof(buf));
	//scan until '<'
	for(i; i < len; i++)
	{
		if(raw_html[i] == '<') break;
	}

	j = i;
	//now scan until '>'
	for(j; j < len; j++)
	{
		buf.push_back(raw_html[j]);
		if(raw_html[j] == '>') 
		{
			j++;	
			break;
		}
	}

	/*
	//i points to the index of the first '<' in raw_html
	//j points to the index of the first '>' after the first '<' in raw_html
	//that means that the return string should be length i + j + 1
	tagLength = i + j + 1;
	//init buf
	std::cout << "\t" << "0. buf: " << buf << std::endl;
	buf = (char *) malloc(tagLength);
	memset(buf, '\0', sizeof(buf));

	std::cout << "\t" << "1. buf: " << buf << std::endl;

	//now copy raw_html from i to j + 1 into buf
	memcpy(buf, &raw_html[i], j + 1);
	std::cout << "\t" << "2. buf: " << buf << std::endl;
	*/
	//don't forget to set the current index
	setCurrentIndex(j);
	/*
	const char * ret = buf;
	*/
	return buf;
}

//return the next tag or inner text
std::vector<char> HTMLParser::next()
{
	prevIndices.push(_i);

	int len = getRawHTMLLength();
	int i = _i; //start index into raw_html for start of return string
	int j = _i; //last index into raw_html for end of return string
	int retLen = 0;
	std::vector<char> ret;

//	std::cout << "HTMLParser::next(): starting at : " << i << std::endl;
	for(i; i < len; i++)
	{
		if(raw_html[i] == '<')
		{
			//if we are here then it is either the start of a tag we will want to return
			//or the end of a string that we want to return
//			std::cout << "\tret.size() : " << ret.size() << std::endl;
			//check to see if we have already pushed characters into
			//the return vector. If we have, then we can just return that
			if(ret.size() > 0)
			{
	//			std::cout << "\tsize > 0." << std::endl;
				setCurrentIndex(i);
				return ret;
			}
			else
			{
				//we have an open tag
				//just use the HTMLParser's nextTag method. 
				//but first we have to set the currentIndex because that function starts from there onto it
				setCurrentIndex(i);
				std::cout << std::endl;
				return nextTag();
			}
		}
		if(raw_html[i] != '\t' && raw_html[i] != '\n')
		{
			ret.push_back(raw_html[i]);
		//	std::cout << "\tadd: '" << raw_html[i] << "'" << std::endl;
			//sleep(1);
		}
	}

//	std::cout << std::endl;
	setCurrentIndex(i);
	return ret;
}

//extract the tags name 
//ex: return "p" if passed "</p>"
//ex: return "section" if passed "<        section>"
//ex: return NULL if passed "this is not even close to being a tag"
std::vector<char> HTMLParser::tagname(const char * s) const
{
	//len of the passed string
	int len = strlen(s);
	//std::vector<char> buf;
	//scan until we hit a '<'
	int i = 0;
	for(i; i < len; i++)
	{
		if(s[i] == '<') break;
	}
	//i will now be pointing to the first '<' (only '<')
	//if i == len-1 then there is no '<', which means it is not a tag
	/*
	if(i == len - 1)
	{
		//not a tag return NULL
		return NULL;
	}
	*/
	//if we are here then it is probably a valid tag
	//i is the start of the string, so we can init a buffer 
	//of len - i, or len - all the characters at the start
	std::vector<char> buf (len - i);
	int j = 0; //index into buf
	
	//open tags can have ids and classes and attributes, but the first string after the < will be the tagname
	//start by scanning until the first character
	while(s[i] == ' ') i++;
	//make sure we are not at a '/'
	while(s[i] == '/') i++;
	//we are now pointing at the first character. From here we can can until either ' ' or '>' which will indicate the end of the tag name
	char c = s[i];
	while(c != ' ' && c != '>')
	{
		buf.push_back(c);
		j++;
	}

	//const char * ret = buf;
	return buf;
}
std::vector<char> HTMLParser::tagname(const std::string s) const
{
	return tagname(s.c_str());
}

//cmp the two tags
//return 0 if equal
//return -1 if a < b
//return 1 if a > b
int HTMLParser::cmpTags(const char * a, const char * b) const
{
	std::vector<char> aN = tagname(a);
	std::vector<char> bN = tagname(b);

	std::string aS (aN.begin(), aN.end());
	std::string bS (bN.begin(), bN.end());

	return aS.compare(bS);
}
int HTMLParser::cmpTags(const std::string a, const std::string b) const
{
	return cmpTags(a.c_str(), b.c_str());
}


//return t/f if s is a close tag
bool HTMLParser::isCloseTag(const char * s) const
{
	int len = strlen(s);
	bool closeTag = false;

	for(int i = 0; i < len; i++)
	{
		if(s[i] == '/')
		{
			closeTag = true;
			break;
		}
		else if (s[i] != '<' || s[i] != ' ')
		{
			//if the char is not an open tag, a space, or a '/' then it cannot be a close tag
			closeTag = false;
			break;
		}
	}

	return closeTag;
}

bool HTMLParser::isCloseTag(const std::string s) const
{
	return isCloseTag(s.c_str());
}

//return t/f if s is a tag
//s will be a tag if it has a '<' followed by a '>'
bool HTMLParser::isTag(const char * s) const
{
	bool isTag = false;
	int len = strlen(s);
	int i = 0;
	//start by scanning until '<'
	for(i; i < len; i++)
	{
		if(s[i] == '<') break;
	}

//	std::cout << "\tisTag: " << i << std::endl;
	int j = len - 1;
	//now start from the back until we hit a '>'
	for(j; j > i; j--)
	{
		if(s[j] == '>')
		{
			isTag = true;
			break;
		}
	}

	return isTag;

}

bool HTMLParser::isTag(const std::string s) const
{
	return isTag(s.c_str());
}
