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
		StorageEngine * elements;

		int _size;
		int current;

		bool empty;

		void setSize(int);
		void setCurrent(int);
		void setElements(StorageEngine *);

		void addElement(Element *);

	public:
		ElementCollection(StorageEngine *);
		ElementCollection(std::vector<Element *>);
		
		bool hasNext();
		Element * next();

		bool isEmpty() const;
		int size() const;
		int getCurrent() const;
		StorageEngine * getElements() const;

};

#endif