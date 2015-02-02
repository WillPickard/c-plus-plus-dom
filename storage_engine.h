//storage_engine.h
#ifndef STORAGE_ENGINE_H
#define STORAGE_ENGINE_H

class Element;

#include "element.h"

#include <vector>

//act as a tree node
struct Bucket
{
	std::vector<Element *> elements;
	std::string index;
	Bucket * left;
	Bucket * right;
};

class StorageEngine
{
	private:
		int _size;
		bool empty;
		struct Bucket * root;

		void setSize(int);
		void setEmpty(bool);
		void setRoot(struct Bucket *);

	public:
		void put(std::string, Element *);
		Element * get(std::string) const;;

		int size() const;
		bool isEmpty() const;
};

#endif