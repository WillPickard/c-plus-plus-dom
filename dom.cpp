//dom.cpp

#include "dom.h"
#include <stack>//stack
#include <queue>//queue
#include <unistd.h>
#include <stdlib.h>
#include "html_parser.cpp" //HTMLParser
/****


class DOM
{
	private:
		const char * raw_html;
		Element * root;

		StorageEngine * id_store; //used to store pointers to elements with ids extracted from the text
		StorageEngine * class_store; //used to store pointers to elements with class from the text
		StorageEngine * tag_name_store; //used to store pointers to elements with prop_types like 'p' or 'div'
		StorageEngine * attr_store; //used to store points to elements with attributes

		void setRawHTML(const char *);
		void setRawHTML(const std::string);
		void setIdStore(StorageEngine *);
		void setClassStore(StorageEngine *);
		void setTagNameStore(StorageEngine *);
		void setAttrStore(StorageEngine *);

	public:
		DOM(const char *);
		DOM(const std::string);

		ElementCollection * find(const char *);
		ElementCollection * find(const std::string);
		ElementCollection * getElementById(const char *);
		ElementCollection * getElementsByClassName(const char *);
		ElementCollection * getElementsByTagName(const char *);
		ElementCollection * getElementsByAttrName(const char *);

		StorageEngine * getIdStore() const;
		StorageEngine * getClassStore() const;
		StorageEngine * getTagNameStore() const;
		StorageEngine * getAttrStore() const;
		const char * getRawHTML() const;
		Element * getRoot() const;
};


**/

DOM::DOM(const std::string html)
{
	DOM(html.c_str());
}

DOM::DOM(const char * html)
{
	setRawHTML(html);

	HTMLParser * parser = new HTMLParser(html);

	std::queue<std::string> tags;
	std::vector<char> current;
	std::string s;
	std::cout << "constructing dom" << std::endl;
	while(parser->hasMore())
	{
		current = parser->next();
		s.assign(current.begin(), current.end());
		tags.push(s);
	}

	while(!tags.empty())
	{
		std::cout << tags.front() << std::endl;
		tags.pop();
	}
}


void DOM::setRawHTML(const char * html)
{
	raw_html = html;
}

void DOM::setRawHTML(const std::string html)
{
	setRawHTML(html.c_str());
}


void DOM::setIdStore(StorageEngine * e)
{
	id_store = e;
}

void DOM::setClassStore(StorageEngine * e)
{
	class_store = e;
}

void DOM::setTagNameStore(StorageEngine * e)
{
	tag_name_store = e;
}

void DOM::setAttrStore(StorageEngine * e)
{
	attr_store = e;
}

ElementCollection * DOM::find(const char *)
{

}

ElementCollection * DOM::find(const std::string)
{

}

ElementCollection * DOM::getElementById(const char *)
{

}

ElementCollection * DOM::getElementsByClassName(const char *)
{

}

ElementCollection * DOM::getElementsByTagName(const char *)
{

}

ElementCollection * DOM::getElementsByAttrName(const char *)
{

}

StorageEngine * DOM::getIdStore() const
{

}

StorageEngine * DOM::getClassStore() const
{

}

StorageEngine * DOM::getTagNameStore() const
{

}

StorageEngine * DOM::getAttrStore() const
{

}

const char * DOM::getRawHTML() const
{

}

Element * DOM::getRoot() const
{

}