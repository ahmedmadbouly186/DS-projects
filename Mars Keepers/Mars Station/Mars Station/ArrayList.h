#pragma once
#include "ListADT.h"
#include<iostream>
#include <string>
template < class ItemType>
class ArrayList : public ListInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 400;
	ItemType items[DEFAULT_CAPACITY + 1]; // Array of list items
	int itemCount; // Current count of list items
	int maxItems; // Maximum capacity of the list
public:
	ArrayList();
	// Copy constructor and destructor are supplied by compiler
	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();
	ItemType getEntry(int position) const;
	ItemType replace(int position, const ItemType& newEntry);
}; // end ArrayList

template < class ItemType>
ArrayList<ItemType>::ArrayList() : itemCount(0),
maxItems(DEFAULT_CAPACITY)
{
}
template < class ItemType>
bool ArrayList<ItemType>::isEmpty() const
{
	return itemCount == 0;
} // end isEmpty
template < class ItemType>
int ArrayList<ItemType>::getLength() const
{
	return itemCount;
} // end getLength 


template < class ItemType>
bool ArrayList<ItemType>::insert(int newPosition,
	const ItemType& newEntry)
{
	bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1) && (itemCount < maxItems);
	if (ableToInsert)
	{
		for (int pos = itemCount; pos >= newPosition; pos--)
			items[pos + 1] = items[pos];
		// Insert new entry
		items[newPosition] = newEntry;
		itemCount++; // Increase count of entries
	} // end if
	return ableToInsert;
} // end insert 

template < class ItemType>
ItemType ArrayList<ItemType>::getEntry(int position) const
{
	// Enforce precondition
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
		return items[position];
	else
	{
		std::string message = "getEntry() called with an empty list or ";
		message = message + "invalid position.";
		std::cout << message << std::endl;
	} // end if
} // end getEntry 

template < class ItemType>
ItemType ArrayList<ItemType>::replace(int position, const ItemType& newEntry)
{
	bool ableToSet = (position >= 1) && (position <= itemCount);
	if (ableToSet)
	{
		ItemType oldEntry = items[position];
		items[position] = newEntry;
		return oldEntry;
	}
	else
	{
		std::string message = "replace() called with an empty list or invalid position.";
		message = message + "invalid position.";
		std::cout << message << std::endl;
	} // end if
} // 

template<class ItemType>
bool ArrayList<ItemType>::remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		for (int pos = position; pos < itemCount; pos++)
			items[pos] = items[pos + 1];
		itemCount--;
	}
	return ableToRemove;
}
template<class ItemType>
void ArrayList<ItemType>::clear()
{
	itemCount = 0;
}


