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

	std::stack<std::string> text;
	std::stack<Element *> elements;

	std::vector<char> current;
	std::string tag;

	current = parser->next();
	tag.assign(current.begin(), current.end());

	bool declaration = false;
	for(int i = 0; i < tag.length(); i++)
	{
		if(tag[i] == ' ') continue;
		if(tag[i] == '<') continue;
		if(tag[i] == '!')
		{
			declaration = true;
			break;
		}
		else break;
	}

	if(declaration)
	{
		Element * dec = new Element(tag);
	}
	else
	{
		parser->rewind(tag.length());
	}
	//stack.push(tag);

	//2d vector of elements
	//elements in v.at(0) have children v.at(1) and etc.
	std::vector< std::vector<Element *> > ele;
	int type;
	Element * e;
	int indent = 0;
	while(parser->hasMore())
	{
		current = parser->next();
		tag.assign(current.begin(), current.end());
		type = parser->getTagType(tag);
		//std::cout << tag << std::endl;

		if(parser->isTag(tag))
		{
			if(type == HTMLParser::tag_type_open || type == HTMLParser::tag_type_full)
			{
				if(type == HTMLParser::tag_type_open)
				{
					indent++;
				}
				/** extract the element's attributes **/
				std::vector<char> tn = parser->tagname(tag);
				std::string tagname (tn.begin(), tn.end());

				std::vector<char> iv = parser->id(tag);
				std::string id (iv.begin(), iv.end());
				
				std::vector< std::vector<char> > cv = parser->classes(tag);
				std::vector< std::string > classes;
				for(int i = 0; i < cv.size(); i++)
				{
					std::string temp (cv.at(i).begin(), cv.at(i).end());
					classes.push_back(temp);
				}
				std::vector< std::array<std::string, 2> > attrsA = parser->attrs(tag);
				std::string innerText = "";
				/** done with attrs **/
				if(!text.empty())
				{
					while(!text.empty())
					{
						innerText += text.top();
						text.pop();
					}
				}
				e = new Element(id, tagname, classes, attrsA, innerText);

				if(ele.size() <= indent)
				{
					int diff = (indent + 1) - ele.size();
					for(int i = 0; i < diff; i++)
					{
						std::vector<Element *> t;
						ele.push_back(t);
					}
				}

				ele.at(indent).push_back(e);
			}
			else if (type == HTMLParser::tag_type_closed)
			{
				indent--;
			}
		}

		
		else
		{
			std::cout << "adding " << tag << " to " << ele.at(indent).back()->getTagName() << std::endl;
			ele.at(indent).at(ele.at(indent).size() - 1)->addInnerText(tag);
			std::cout << "done adding" << std::endl;
		}
	
	}//while

	std::cout << "done" << std::endl;
	for(int i = 0; i < ele.size(); i++)
	{
		for(int j = 0; j < ele.at(i).size(); j++)
		{
			std::string indent = "";
			for(int c = 0; c < i; c++) indent += "\t";
			std::cout << indent << ele.at(i).at(j)->getTagName() << " : " << ele.at(i).at(j)->getText() << std::endl;
		}
	}
	/**
	std::cout << "elements.size() : " << elements.size() << std::endl;
	while(!elements.empty())
	{
		e = elements.top();
		elements.pop();
		std::cout << "\t" << e->getRawHTML() << std::endl;
		std::cout << "\t" << "num children : " << e->children() << std::endl;
	}
	**/
}


void DOM::setRawHTML(const char * html)
{
	raw_html = html;
}

void DOM::setRawHTML(const std::string html)
{
	setRawHTML(html.c_str());
}

/**
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
**/
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

/*
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
*/
const char * DOM::getRawHTML() const
{

}

Element * DOM::getRoot() const
{

}