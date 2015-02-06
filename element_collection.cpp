//element_collection.cpp

#include "element_collection.h"

//#include "storage_engine.cpp"

//default constructor
ElementCollection::ElementCollection():
	_size(0),
	current(-1),
	empty(true)
	{
		id_store = new StorageEngine();
		class_store = new StorageEngine();
		tag_name_store = new StorageEngine();
		attr_store = new StorageEngine();
	}

//with the collection's elements
ElementCollection::ElementCollection(std::vector<Element *> elements):
	_size(elements.size()),
	current(0),
	empty(false)
	{
		Element * root = elements.at(0);

		std::string id = root->getId();
		std::string tagname = root->getTagName();
		std::vector<std::string> classes = root->getClassNames();
		std::vecotr< std::array<std::string, 2> > attrs = root->getAttrs();

		id_store = new StorageEngine(id, root);
		class_store = new StorageEngine();
	}

void ElementCollection::setSize(int i)
{

}
void ElementCollection::setCurrent(int c)
{

}
void ElementCollection::setElements(StorageEngine * e)
{

}

ElementCollection::ElementCollection(StorageEngine * s)
{
}

ElementCollection::ElementCollection(std::vector<Element *> s)
{

}

/***
* add the Element s to the various stores
*	add it to the vector of all
*	add it to the id_store
*	add it to the class_store
*	add it to the tag_name_store
*	add it to the attr_store
***/
void ElementCollection::add(Element * e)
{
	//when we are adding an Element to a collection then we need to 
	//make sure that we index all of its various attributes
	//as well as pushing it into the all Element vector
	std::string id = e->getId();
	std::string tagname = e->getTagName();
	std::vector<std::string> classes = e->getClassNames();
	std::vector< std::array<std::string, 2> > attrs = e->getAttrs();
	//handle id

	//put it in the vector too
	getElements().push_back(e);
}
bool ElementCollection::hasNext()
{

}
Element * ElementCollection::next()
{

}
bool ElementCollection::isEmpty() const
{

}
int ElementCollection::size() const
{

}
int ElementCollection::getCurrent() const
{

}
std::vector<Element *> ElementCollection::getElements() const
{
	return elements;
}
