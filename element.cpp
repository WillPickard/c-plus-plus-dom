//element.cpp

#include "element.h"


Element::Element(const char * s)
{
//	std::string temp (s, strlen(s));
//	Element((const)temp);
}
Element::Element(const std::string s)
{
	setRawHTML(s);

	//scan for inner text
	std::string text = "";
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] == '>')
		{
			for(i; i < s.length(); i++)
			{
				text += s[i];
			}
		}
	}
	setInnerText(s);
}
//id, tagName, classNames, attrs
Element::Element( std::string id,  std::string tagname,  std::vector<std::string> classnames,  std::vector< std::array<std::string, 2> > attrs):
	id(id),
	tagName(tagname),
	classNames(classnames),
	attrs(attrs)
	{};
	
//id, tagName, classNames, attrs, innerText
Element::Element( std::string id,  std::string tagname,  std::vector<std::string> classnames,  std::vector< std::array<std::string, 2> > attrs,  std::string innerText):
	Element(id, tagname, classnames, attrs)
	{
		setInnerText(innerText);
	};

void Element::setId( std::string s)
{
	id = s;
}
void Element::setTagName( std::string s)
{
	tagName = s;
}
void Element::setClassName( std::vector<std::string> s)
{
	classNames = s;
}
void Element::setAttrs( std::vector< std::array<std::string, 2> > a)
{
	attrs = a;
}
void Element::setInnerText( std::string s)
{
	innerText = s;
}
void Element::setRawHTML( std::string s)
{
	raw_html = s;
}

void Element::setParent( Element * p)
{
	_parent = p;
}
void Element::setParents( ElementCollection * p)
{
	_parents = p;
}
void Element::setChildren( ElementCollection * c)
{
	_children = c;
}
void Element::setSiblings( ElementCollection * s)
{
	_siblings = s;
}	



void Element::addClass( std::string s)
{
	getClassNames().push_back(s);
}
void Element::addAttr(std::string key, std::string value)
{
	//getAttrs().push_back(a);
}
void Element::addParent( Element * p)
{
	parents()->add(p);
}
void Element::addChild( Element * c)
{
	children()->add(c);
}
void Element::addSibling( Element * s)
{
	siblings()->add(s);
}
void Element::addInnerText( std::string s)
{
	setInnerText(getText() + s);
}

std::string Element::getId() const
{
	return id;
}
std::string Element::getTagName() const
{
	return tagName;
}
std::vector<std::string> Element::getClassNames() const
{	
	return classNames;
}
std::vector< std::array<std::string, 2> > Element::getAttrs() const
{
	return attrs;
}
std::string Element::getText() const
{
	return innerText;
}
std::string Element::getRawHTML() const
{
	return raw_html;
}

Element * Element::parent() const
{
	return _parent;
}

ElementCollection * Element::parents() const
{
	return _parents;
}
ElementCollection * Element::parents(const std::string s) const
{
	return _parents;
}

ElementCollection * Element::children() const
{
	return _children;
}
ElementCollection * Element::children(const std::string s) const
{
	return _children;
}

ElementCollection * Element::siblings() const
{
	return _siblings;
}
ElementCollection * Element::siblings(const std::string s) const
{	
	return _siblings;
}
