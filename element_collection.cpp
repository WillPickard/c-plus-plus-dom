//element_collection.cpp

#include "element_collection.h"

//#include "storage_engine.cpp"

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
void ElementCollection::add(Element * s)
{
	//getElements()->put(s);
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
