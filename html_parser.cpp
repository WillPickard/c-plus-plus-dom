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
				//but first we have to set the currentIndex because that function starts from there 
				setCurrentIndex(i);
				//std::cout << std::endl;
				return nextTag();
			}
		}
		if(!isEscapeSequence(raw_html[i]))
		{
			ret.push_back(raw_html[i]);
			//std::cout << "\tadd: '" << raw_html[i] << "' " << strlen(&raw_html[i]) << " to int: " << (int) raw_html[i] << std::endl;
			//sleep(1);
		}
	}

//	std::cout << std::endl;
	setCurrentIndex(i);
	return ret;
}

//return a vector of characters for the key in the tag
std::vector<char> HTMLParser::valueString(const char * tag, const char * key) const
{
//	std::cout << "------- looking for value of " << key << " in " << tag << std::endl;
	std::vector<char> ret; //return vctor

	if(!isOpenTag(tag) && !isCloseTag(key))
	{
		return ret;
	}

	int taglen = strlen(tag);
	int keylen = strlen(key);
	int i = 0, j = 0, matching;

	//scan until we find the key
	for(i; i < taglen; i++)
	{
		matching = 0;
		while(tag[i] == key[j])
		{
			i++;
			j++;
			matching++;
		}
		//std::cout << "matching : " << matching << " and keylen: " << keylen <<  std::endl;
		//if matching is equal to the tag's length then we have a hit
		if(matching == keylen)
		{
			//scan until ' or "
		//	std::cout << "hit" << std::endl;
			char delim; //this will be either ' or "
			while((tag[i] != '\'' && tag[i] != '"') && i < taglen) i++;
			delim = tag[i];
		//	std::cout << "delim: " << delim << std::endl;
			i++; //i is now pointing to the first character
			char c = tag[i];
			while(c != delim && i < taglen)
			{
		//		std::cout << "\t" << "adding " << c << std::endl;
				ret.push_back(c);
				c = tag[++i];
			}
			return ret;
		}

		matching = 0;
		j = 0;
	}

	return ret;
}
std::vector<char> HTMLParser::valueString(const char * tag, const std::string key) const
{
	return valueString(tag, key.c_str());
}
std::vector<char> HTMLParser::valueString(const std::string tag, const char * key) const
{
	return valueString(tag.c_str(), key);
}
std::vector<char> HTMLParser::valueString(const std::string tag, const std::string key) const
{
	return valueString(tag.c_str(), key.c_str());
}

//extract the tags name 
//ex: return "p" if passed "</p>"
//ex: return "section" if passed "<        section>"
//ex: return NULL if passed "this is not even close to being a tag"
std::vector<char> HTMLParser::tagname(const char * s) const
{
//	std::cout << "determining tagname for tag : " << s << std::endl;
	//len of the passed string
	int len = strlen(s);
	//std::vector<char> buf;
	//scan until we hit a '<'
	int i = 0;
	for(i; i < len; i++)
	{
		//std::cout << "i : " << i << std::endl;
		if(s[i] == '<') break;
	}
	i++;

//	std::cout << "i: " << i << " and len: " << len << std::endl;
	if(i > len)
	{
		return std::vector<char> (0);
	}

	//open tags can have ids and classes and attributes, but the first string after the < will be the tagname
	//start by scanning until the first character
	while(s[i] == ' ') i++;
	//make sure we are not at a '/'
	while(s[i] == '/') i++;
	std::vector<char> buf;// (len - i);
	//we are now pointing at the first character. From here we can can until either ' ' or '>' which will indicate the end of the tag name
	char c = s[i];
	while((i < len) && c != ' ' && c != '>')
	{
	//	std::cout << "\t~ " << c << std::endl;
		buf.push_back(c);
		i++;
		c = s[i];
		//j++;
	}

	//const char * ret = buf;
	return buf;
}

std::vector<char> HTMLParser::tagname(const std::string s) const
{
	return tagname(s.c_str());
}

std::vector<char> HTMLParser::id(const char * s) const
{
	std::vector<char> ret;

	if(!isOpenTag(s) && !isFullTag(s))
	{
		return ret;
	}

	ret = valueString(s, "id");
	return ret;
}
std::vector<char> HTMLParser::id(const std::string s) const
{
	return id(s.c_str());
}

//return a vector of char vectors. Each vector in the parent vector 
//represents a single class seperated by a ' '
std::vector< std::vector<char> > HTMLParser::classes(const char * s) const
{
	std::vector< std::vector<char> > ret;

	if(!isOpenTag(s) && !isFullTag(s))
	{
		return ret;
	}

	std::vector<char> value = valueString(s, "class");
	for(int i = 0; i < value.size(); i++)
	{
		std::vector<char> local;
		while(i < value.size() && value.at(i) != ' ')
		{
			local.push_back(value.at(i));
			i++;
		}
		ret.push_back(local);
	}

	return ret;
	
}
std::vector< std::vector<char> > HTMLParser::classes(const std::string s) const
{
	return classes(s.c_str());
}

//return a vector of arrays where element 0 is the attr name and 1 the value
std::vector< std::array<std::string, 2> > HTMLParser::attrs(const char * s) const
{
	std::vector< std::array<std::string, 2> > ret;

	if(!isOpenTag(s) && !isFullTag(s))
	{
		return ret;
	}

	//ids and classes are included in attr
	//this means we need to scan through all characters
	int len = strlen(s);
	int i = 0, j = 0;
	std::string key;
	std::string value;
	for(i; i < len; i++)
	{
		if(s[i] == '=')
		{
			//std::cout << "\t" << i << std::endl;
			j = i; //no need to go forwards after this after we do what were are about to do
			//key is backwards until ' ' after any ' '
			i--;
			//scan until the first character skipping ' '
			while(s[i] == ' ' && (i) > 0) i--;
			//std::cout << "\t" << i << std::endl;

			key = "";
			//now scan in letters until ' ' or until we have scanned in the whole key
			while(s[i] != ' ' && i > 0)
			{
				char c = s[i--];
			//	std::cout << "\tc : " << c << std::endl;
				key = c + key; //we are going backwards so we have to build it in reverse order
			}	
			std::array<std::string, 2> part;
			//key is now the key
			part[0] = key;
			//std::cout << "\tkey : " << key << std::endl;
			i = j; //save time, i is now pointing to a '='
			i++;
			//scan past ' '
			while(s[i] == ' ' && i < len) i++;
			//i is now pointing to a " or a '
			char delim = s[i];
			i++;
			//scan until close delim scanning into the value
			value = "";
			while(s[i] != delim)
			{
				value += s[i]; //normal order
				i++;
			}
			part[1] = value;
			ret.push_back(part);

		}
	}

	return ret;
}
std::vector< std::array<std::string, 2> > HTMLParser::attrs(const std::string s) const
{
	return attrs(s.c_str());
}


//cmp the two tags
//return 0 if equal
//return -1 if a < b
//return 1 if a > b
int HTMLParser::cmpTags(const char * a, const char * b) const
{
//	std::cout << "cmpTags, a: " << a << ", b: " << b << std::endl;
	std::vector<char> aN = tagname(a);
	std::vector<char> bN = tagname(b);
//	std::cout << "cmpTags vectors, a.size(): " << aN.size() << ", b.size(): " << bN.size() << std::endl;
	std::string aS (aN.begin(), aN.end());
	std::string bS (bN.begin(), bN.end());

//	std::cout << "aS name : " << aS << " and bN name : " << bS << std::endl;

	int r = aS.compare(bS);
//	std::cout << "cmpTags, a: " << aS << "(" << aS.length() << "), b: " << bS << "(" << bS.length() << "). return : " << r << std::endl;
	return r;
}
int HTMLParser::cmpTags(const std::string a, const std::string b) const
{
	return cmpTags(a.c_str(), b.c_str());
}

//t/f if the tag is both an open an close tag
//that is like an img tag: <img src="src" />
//or: <p id="teset">this is a full tag</p>
bool HTMLParser::isFullTag(const char * s) const
{
	int len = strlen(s);
	int i = len - 1;
	bool both = false;
	int required = 0; //required must be 2, that is we must hit a '<' and a '/' if it is a both tag before anything else

	//start left to right
	//scanning for a />
	for(i; i >= 0; i--)
	{
		switch(s[i])
		{
			case '>':
				required++;
				break;
			case '/':
				required++;
				if(required != 2)
				{
					//this means that we encounterd a '/' before a '>'
					return false;
				}
				//break the loop
				i = -1;
				break;
			case '<':
				return false;
			default:
				break;
		}
	}

	//now scan left to right check for a '<' before anything else
	for(i = 0; i < len; i++)
	{
		switch(s[i])
		{
			case '<':
				//we golden
				return true;
			case ' ':
				//ignore
				break;
			default:
				return false;
		}
	}

	return both;
}

bool HTMLParser::isFullTag(const std::string s) const
{
	return isFullTag(s.c_str());
}

//return t/f if s is a close tag
bool HTMLParser::isCloseTag(const char * s) const
{
	int len = strlen(s);
	bool closeTag = false;

	for(int i = 0; i < len; i++)
	{
//		std::cout << s[i] << std::endl;
		if(s[i] == '/')
		{
//			std::cout << "1" << std::endl;
			closeTag = true;
			break;
		}
		else if (s[i] != '<' && s[i] != ' ')
		{
//			std::cout << "2" << std::endl;
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

//return t/f if s is an open tag
bool HTMLParser::isOpenTag(const char * s) const
{
	int len = strlen(s);
	bool openTag = true;
	int i = 0;
	int j = (len - 1);
	//make sure we have a tag (starts with '<')
	for(i; i < len; i++)
	{
		if(s[i] == '<')
		{
			i++;
			break;
		}
		else if(s[i] == ' ') continue;
		else return false;
	}

	//check for a '/' at the beginning of the tag
	for(i; i < len; i++)
	{
		if(s[i] == '/') return false;
		else if(s[i] == ' ') continue;
		else
		{
			i++;
			break;
		}
	}

	//now check to see if it is a both tag (has a '/' at the back)
	for(j; j >= i; j--)
	{
		if(s[j] == '>') continue;
		else if(s[j] == ' ') continue;
		else if(s[j] == '/') return false;
		else continue;
	}
	return openTag;
}

bool HTMLParser::isOpenTag(const std::string s) const
{
	return isOpenTag(s.c_str());
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

signed char HTMLParser::getTagType(const char * s) const
{
	signed char result = HTMLParser::tag_type_none;

	if(isTag(s))
		result |= HTMLParser::tag_type_tag;
	else
		return result;

	if(isOpenTag(s))
		result |= HTMLParser::tag_type_open;
	else if(isCloseTag(s))
		result |= HTMLParser::tag_type_closed;
	else if(isFullTag(s))
		result |= HTMLParser::tag_type_full;

	return result;
}

signed char HTMLParser::getTagType(const std::string s) const
{
	return getTagType(s.c_str());
}

bool HTMLParser::isEscapeSequence(char c) const
{
	/** not in switch:
			'\\' - backslash
			'\?' - questionmark
			'\ooo' - octal
			'\xhhh' - hexadecimal
			'\uxxx' - utf-8
			'\Uxxxxxxxx' - utf-16
	**/
	switch(c)
	{
		case '\n': //new line
		case '\t': //horizontal tab
		case '\v': //vertial tab
		case '\b': //backspace
		case '\r': //carriage return
		case '\f': //form feed
		case '\a': //alert
		case '\0': //null
			return true;
		default:
			return false;
	}
}

bool HTMLParser::isTag(const std::string s) const
{
	return isTag(s.c_str());
}
