//element.h
#ifndef ELEMENT_H
#define ELEMENT_H

#ifndef STORAGE_ENGINE_H
#include "element_collection.h"
#endif

#include <string>
#include <vector>

class Element
{
	private:
		std::string id;
		std::string tagName;
		std::vector<std::string> classNames;
		std::vector<std::string> attrs;
		std::string innerText;
		std::string raw_html;

		Element * _parent;
		ElementCollection * _parents;	
		ElementCollection * _children;
		ElementCollection * _siblings;

		void setId( std::string);
		void setTagName( std::string);
		void setClassName( std::vector<std::string>);
		void setAttrs( std::vector<std::string>);
		void setInnerText( std::string);
		void setRawHTML( std::string);

		void setParent( Element *);
		void setParents( ElementCollection *);
		void setChildren( ElementCollection *);
		void setSiblings( ElementCollection *);

	public:
		Element(const char *);
		Element(const std::string);
		//id, tagName, classNames, attrs
		Element( std::string,  std::string,  std::vector<std::string>,  std::vector<std::string>);
		//id, tagName, classNames, attrs, innerText
		Element( std::string,  std::string,  std::vector<std::string>,  std::vector<std::string>,  std::string innerText);

		void addClass( std::string);
		void addAttr( std::string);
		void addParent( Element *);
		void addChild( Element *);
		void addSibling( Element *);
		void addInnerText( std::string);

		std::string getId() const;
		std::string getTagName() const;
		std::vector<std::string> getClassNames() const;
		std::vector<std::string> getAttrs() const;
		std::string getText() const;
		std::string getRawHTML() const;

		Element * parent() const;

		ElementCollection * parents() const;
		ElementCollection * parents(const std::string) const;

		ElementCollection * children() const;
		ElementCollection * children(const std::string) const;

		ElementCollection * siblings() const;
		ElementCollection * siblings(const std::string) const;
};


#endif