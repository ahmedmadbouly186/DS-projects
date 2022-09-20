#pragma once
#include "Node.h"
#include "QueueADT.h"
#include <vector>
using namespace std;
template <typename T>
class LinkedQueue:public QueueADT<T>
{
private :
	
	Node<T>* backPtr;
	Node<T>* frntPtr;
	int count;
public :
	LinkedQueue();	
	bool isEmpty() const ;
	bool enqueue(const T& newentry);
	bool dequeue(T& frntentry);  
	bool peek(T& frntentry)  const;	
	int getcount() { return count; }
	~LinkedQueue();
	//copy constructor
	LinkedQueue(const LinkedQueue<T> & LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr=nullptr;
	frntPtr=nullptr;
	count = 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frntPtr ==nullptr);
}
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool LinkedQueue<T>::enqueue( const T& newentry)
{
	count++;
	Node<T>* newNode = new Node<T>(newentry);
	// Insert the new node
	if (isEmpty())
		frntPtr = newNode;
	else
		backPtr->setNext(newNode);

	backPtr = newNode;
	return true ;
} // end enqueue
/////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool LinkedQueue<T>:: dequeue(T& frntentry)  
{
	if(isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frntPtr;
	frntentry = frntPtr->getItem();
	frntPtr = frntPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 
		backPtr = nullptr ;	
		
	delete nodeToDeletePtr;
	count--;
	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool LinkedQueue<T>:: peek(T& frntentry) const 
{
	if(isEmpty())
		return false;

	frntentry = frntPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T Tmp;
	//Dequeue all nodes in the queue
	while(dequeue(Tmp));	
}
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> & Q1)
{	
	Node<T>* NodePtr = Q1.frontPtr;
	if (!NodePtr) 
	{
		frntPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frntPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();
	//insert the remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}	
}

