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

	std::stack<std::string> stack;
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

	int type;
	Element * e;
	while(parser->hasMore())
	{
		current = parser->next();
		tag.assign(current.begin(), current.end());
		type = parser->getTagType(tag);
		std::cout << tag << std::endl;

		if(parser->isTag(tag))
		{
			std::vector<char> tn = parser->tagname(tag);
			std::string tagname (tn.begin(), tn.end());

			std::vector<char> iv = parser->id(tag);
			std::string id (iv.begin(), iv.end());
			
			std::vector< std::vector<char> > cv = parser->classes(tag);
			std::string classes = "";
			for(int i = 0; i < cv.size(); i++)
			{
				std::string temp (cv.at(i).begin(), cv.at(i).end());
				classes += temp + " ";
			}
			std::vector< std::array<std::string, 2> > attrsA = parser->attrs(tag);
			std::string attrs = "";
			for(int i = 0; i < attrsA.size(); i++)
			{
				attrs += attrsA.at(i)[0];
				attrs += "=";
				attrs += attrsA.at(i)[1];
				attrs += " ";
			}


			std::cout << "\t" << "tagname: " << tagname << std::endl;
			std::cout << "\t" << "id: " << id << std::endl;	
			std::cout << "\t" << "classes: " << classes << std::endl;	
			std::cout << "\t" << "attrs: " << attrs << std::endl;	



		}
		
		/**
		switch(type)
		{
			case HTMLParser::tag_type_none:
				elements.top()->addInnerText(tag);
				break;
			case HTMLParser::tag_type_open:
			case HTMLParser::tag_type_full:
				e = new Element(tag);
				elements.push(e);
				break;
			case HTMLParser::tag_type_closed:
				e = elements.top();
				//std::cout << "\t" << "closed, comparing tag: " << tag << " with e raw_html : " << e->getRawHTML() << std::endl;
				while(parser->cmpTags(e->getRawHTML(), tag) != 0)
				{
					elements.pop();
					e = elements.top();
					e->addChild(e);
				}
			case HTMLParser::tag_type_tag:
			default:
				stack.push(tag);
		}
		**/
	
	}//while
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