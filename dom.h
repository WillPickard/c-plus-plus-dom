//dom.h
#ifndef DOM_H
#define DOM_H

#include "element.h"
#include "element_collection.h"
#include "storage_engine.h"

#include <string>
#include <string.h>
#include <iostream>

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

#endif