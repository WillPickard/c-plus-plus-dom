//element_collection.h
#ifndef ELEMENT_COLLECTION_H
#define ELEMENT_COLLECTION_H

class Element;
class StorageEngine;

#include "storage_engine.h"
#include "element.h"

#include <vector>
//#include <cstddef> //nullptr_t

const void * EC_NULL = NULL;

class ElementCollection
{
	private:
		StorageEngine * id_store; //used to store pointers to elements with ids extracted from the text
		StorageEngine * class_store; //used to store pointers to elements with class from the text
		StorageEngine * tag_name_store; //used to store pointers to elements with prop_types like 'p' or 'div'
		StorageEngine * attr_store; //used to store points to elements with attributes

		std::vector<Element *> elements;

		int _size;
		int current;

		bool empty;

		void setSize(int);
		void setCurrent(int);
		void setElements(StorageEngine *);

	public:
		ElementCollection(StorageEngine *);
		ElementCollection(std::vector<Element *>);
		
		void add(Element *);

		bool hasNext();
		Element * next();

		bool isEmpty() const;
		int size() const;
		int getCurrent() const;

		std::vector<Element *> getElements() const;

};

#endif