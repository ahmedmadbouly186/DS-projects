#pragma once
#include "priQueueADT.h"
template <typename T>
struct node
{
	int Priority;
	T Item;
	node<T>* Next = nullptr;
};
template <typename T>
class linkedPriQueue :public priQueueADT<T>
{
private:
	node<T>* frontPtr;
public:
	linkedPriQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, int priority);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	~linkedPriQueue();

	//copy constructor
	linkedPriQueue(const linkedPriQueue<T>& LQ);
};

template <typename T>
linkedPriQueue<T>::linkedPriQueue()
{
	frontPtr = nullptr;
}
template <typename T>
bool linkedPriQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}
template<typename T>
bool linkedPriQueue<T>::enqueue(const T& newentry, int priority)
{
	node <T>* R = new node<T>;
	R->Item = newentry;
	R->Priority = priority;
	if (!R)return false;
	if (isEmpty() || R->Priority > frontPtr->Priority)
	{
		R->Next = frontPtr;
		frontPtr = R;
		return true;
	}
	node<T>* ptr = frontPtr;
	while (ptr->Next && !(R->Priority > ptr->Next->Priority))
	{
		ptr = ptr->Next;
	}
	R->Next = ptr->Next;
	ptr->Next = R;
	return true;
}


template<typename T>
bool linkedPriQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->Item;
	frontPtr = frontPtr->Next;
	// Queue is not empty; remove front

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;
}
template <typename T>
bool linkedPriQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->Item;
	return true;

}
template <typename T>
linkedPriQueue<T>::~linkedPriQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}
template <typename T>
linkedPriQueue<T>::linkedPriQueue(const linkedPriQueue<T>& LQ)
{
	node<T>* NodePtr = LQ.frontPtr;
	node<T>* backPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = nullptr;
		return;
	}

	//insert the first node
	node<T>* ptr = new node<T>(NodePtr->Item);
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->Next;

	//insert remaining nodes
	while (NodePtr)
	{
		node<T>* ptr = new node<T>(NodePtr->Item);
		backPtr->Next = ptr;
		backPtr = ptr;
		NodePtr = NodePtr->Next;
	}
}