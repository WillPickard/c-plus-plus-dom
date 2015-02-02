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

	//vector of raw tags
	std::vector<const char *> raw_tags;
	std::stack<char> chars;
	std::stack<const char *> partial_tags;
	std::queue<const char *> tags;
	bool isCloseTag = false; //set to true when it is a closing tag (has '/')
	//number of characters in the html
	int len = strlen(html);
	//iterate through all of the characters, pushing them onto the character stack
	std::string openTag = "";
	std::string closeTag = "";
	std::string innerText = "";
	std::string fullTag = "";
	std::size_t str_length;
	char *cT, *fT, *oT, *iT;
	for(int i = 0; i < len; i++)
	{
		char c = html[i];
		chars.push(c);

		switch(c)
		{
			case '<':
				if(html[i + 1] == '/')
				{
					//close tag
					chars.push(html[i + 1]);
					i += 2;
					c = html[i];

					//close tag encountered
					while(c != '>')
					{
						c = html[i++];
						chars.push(c);
					}
					//c is '>'
					// /chars.push(c);
					closeTag = "";
					while(c != '<')
					{
						c = chars.top();
						chars.pop();
						closeTag = c + closeTag;
					}
				//	std::cout << closeTag << std::endl;

					cT = (char *) malloc(closeTag.length() + 1);
					str_length = closeTag.copy(cT, closeTag.length(), 0);
					cT[str_length] = '\0';
				//	tags.push(cT);
				//	partial_tags.push(cT);
				//	std::cout << "closeTag : " << partial_tags.top() << std::endl;
					//closeTag = "";
					//now iterate threw the characters if there are any
					if(!chars.empty())
					{
						innerText = "";
						while(!chars.empty())
						{
							c = chars.top();
							chars.pop();
							innerText = c + innerText; 
						}

						//now push the inner text on first. Then the close tag
						iT = (char *) malloc(innerText.length() + 1);
						str_length = innerText.copy(iT, innerText.length(), 0);
						iT[str_length] = '\0';
						tags.push(iT);
					}
					tags.push(cT);

				//	closeTag = partial_tags.top();
				//	std::cout << "closeTag: " << partial_tags.top() << std::endl;
				//	partial_tags.pop();

				//	openTag = partial_tags.top();
				//	partial_tags.pop();

				//	fullTag = openTag + innerText + closeTag;
				//	fT = (char *) malloc(fullTag.length() + 1);
				//	str_length = fullTag.copy(fT, fullTag.length(), 0);
					//fT[str_length] = '\0';
				//	std::cout << fullTag << std::endl;
				//	sleep(2);
					//raw_tags.push_back(fT);
				}
				else
				{
					//open tag. just push it onto the stack and let the next case handle it
				//	chars.push(c);
				}
				break;
			case '>':
				//end of open tag
				chars.pop();
				openTag = c;
				while(!chars.empty())
				{
					c = chars.top();
					chars.pop();
					openTag = c + openTag;
				}
				oT = (char *) malloc(openTag.size() + 1);
				str_length = openTag.copy(oT, openTag.size(), 0);
				oT[str_length] = '\0';
				tags.push(oT);
			//	partial_tags.push(oT);
				break;
			default:
				//chars.push(c);
				break;
		}
	}

	//now make the dom 
	if(!tags.empty())
	{
		std::queue<const char *> tagsToProcess;

		const char * firstTag = tags.front();
		if(strlen(firstTag) >= 2 && firstTag[1] == '!')
		{
			//the document declaration tag
			//pop it off
			const char * docType = firstTag;
			tags.pop();
			
		}
		
		//now the root will be whatever is on the top
		tagsToProcess.push(tags.front());
		tags.pop();
		while(!tagsToProcess.empty())
		{
			const char * tag = tags.front();
			tags.pop();
			//put it on the toProcess
			tagsToProcess.push(tag);
			//check to see if it was a closetag
			if(strlen(tag) >= 2 && tag[1] == '/')
			{
				std::string fullTag = tag;
				//if it is a closing tag, then pop til you get its counter part
				size_t closeTagLength = strlen(tag);
				//we subtract 3 because the close tag has 3 chars that do not distinguish its tag type (</p> - only need the p)
				int actualTagLength = closeTagLength - 3;

				char cleanCloseTag[actualTagLength], openCloseTag[actualTagLength];
				//substr
				memcpy(cleanCloseTag, &tag[1], actualTagLength);

				tag = tags.front();
				if(strlen(tag) > actualTagLength + 2)
				{
					//if it is 2 greater than the actual tag length 
				}
			}
		}	
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