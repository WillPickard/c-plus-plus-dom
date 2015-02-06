//storage_engine.cpp
#include "storage_engine.h"


/****

	act as a tree node
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
			setRoot(struct Bucket *);

		public:
			void put(std::string, Element *);
			Element * get(std::string) const;;

			int size() const;
			bool isEmpty() const;
	};

****/
StorageEngine::StorageEngine():
	_size(0),
	empty(true)
	{
		root = NULL;
	}
//constructor with a root, use the tags name as the idnex if none if provided
StorageEngine::StorageEngine(Element * e):
	_size(1),
	empty(false)
	{
		struct Bucket r;
		std::string i = e->getTagName();
		r.elements.push_back(e);
		r.index = i;
		r.left = NULL;
		r.right = NULL;

		root = &r;
	}
//construct the engine with a index
StorageEngine::StorageEngine(std::string i, Element * e):
	_size(1),
	empty(false)
	{
		struct Bucket r;

		r.elements.push_back(e);
		r.index = i;
		r.left = NULL;
		r.right = NULL;

		root = &r;
	}
void StorageEngine::setSize(int s)
{
	_size = s;
}

void StorageEngine::setEmpty(bool e)
{
	empty = e;
}

void StorageEngine::setRoot(struct Bucket * b)
{
	root = b;
}

void StorageEngine::put(std::string index, Element * e)
{

}	

Element * StorageEngine::get(std::string index) const
{

}

int StorageEngine::size() const
{
	return _size;
}

bool StorageEngine::isEmpty() const
{
	return empty;
}



