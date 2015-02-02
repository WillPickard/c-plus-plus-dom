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



