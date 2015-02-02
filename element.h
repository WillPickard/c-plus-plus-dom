//element.h
#ifndef ELEMENT_H
#define ELEMENT_H

#include "element_collection.h"

#include <string>
#include <vector>

class Element
{
	private:
		const std::string id;
		const std::string tagName;
		const std::vector<std::string> classNames;
		const std::vector<std::string> attrs;
		const std::string innerText;

		const Element * _parent;
		const ElementCollection * _parents;	
		const ElementCollection * _children;
		const ElementCollection * _siblings;

		void setId(const std::string);
		void setTagName(const std::string);
		void setClassName(const std::vector<std::string>);
		void setAttrs(const std::vector<std::string>);
		void setInnerText(const std::string);

		void setParent(const Element *);
		void setParents(const ElementCollection *);
		void setChildren(const ElementCollection *);
		void setSiblings(const ElementCollection *);

		void addClass(const std::string);
		void addAttr(const std::string);
		void addParent(const Element *);
		void addChild(const Element *);
		void addSibling(const Element *);

	public:
		Element(const char *);
		Element(const std::string);
		//id, tagName, classNames, attrs
		Element(const std::string, const std::string, const std::vector<std::string>, const std::vector<std::string>);
		//id, tagName, classNames, attrs, innerText
		Element(const std::string, const std::string, const std::vector<std::string>, const std::vector<std::string>, const std::string innerText);


		const std::string getId() const;
		const std::string getTagName() const;
		const std::vector<std::string> getClassNames() const;
		const std::vector<std::string> getAttrs() const;
		const std::string getText() const;

		Element * parent() const;

		ElementCollection * parents() const;
		ElementCollection * parents(const std::string) const;

		ElementCollection * children() const;
		ElementCollection * children(const std::string) const;

		ElementCollection * siblings() const;
		ElementCollection * siblings(const std::string) const;
};


#endif