#pragma once
#include "priQueueADT2.h"
#include "Pair.h"
#include "Node.h"
template <typename T1, typename T2>
class linkedPriQueue2 :public priQueueADT2<T1, T2>
{
private:
	Node<Pair<T1, T2>>* frontPtr;
	int count;
public:
	linkedPriQueue2();
	bool isEmpty() const;
	bool enqueue(const Pair<T1,T2>& newentry);
	bool dequeue(T1& frntEntry);
	bool peek(T1& frntEntry)  const;
	~linkedPriQueue2();
	int getcount() { return count; }
	//copy constructor
	linkedPriQueue2(const linkedPriQueue2<T1,T2>& LQ);
};

template <typename T1, typename T2>
linkedPriQueue2<T1, T2>::linkedPriQueue2()
{
	frontPtr = nullptr;
	count = 0;
}


template <typename T1, typename T2>
bool linkedPriQueue2<T1, T2>::isEmpty() const
{
	return (frontPtr == nullptr);
}
template <typename T1, typename T2>
bool linkedPriQueue2<T1, T2>::enqueue(const Pair<T1,T2>& newentry)
{
	Node<Pair<T1, T2>>* R = new Node<Pair<T1, T2>>(newentry);

	if (!R)return false;
	if (isEmpty() || R->getItem() > frontPtr->getItem())
	{
		R->setNext(frontPtr);
		frontPtr = R;
		count++;
		return true;
	}
	Node<Pair<T1, T2>>* ptr = frontPtr;
	while (ptr->getNext() && !(R->getItem() > ptr->getNext()->getItem()))
	{
		ptr = ptr->getNext();
	}
	R->setNext(ptr->getNext());
	ptr->setNext(R);
	count++;
	return true;
}
template <typename T1, typename T2>
bool linkedPriQueue2<T1, T2>::dequeue(T1& frntEntry)
{
	if (isEmpty())
		return false;

	Node<Pair<T1,T2>>* nodeToDeletePtr = frontPtr;
	Pair<T1, T2> p = frontPtr->getItem();
	frntEntry = p.getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	count--;
	return true;
}
template <typename T1, typename T2>
bool linkedPriQueue2<T1, T2>::peek(T1& frntEntry) const
{
	if (isEmpty())
		return false;
	Pair<T1,T2>p= frontPtr->getItem();
	frntEntry = p.getItem();
	return true;

}
template <typename T1, typename T2>
linkedPriQueue2<T1, T2>::~linkedPriQueue2()
{
	T1 temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}
template <typename T1, typename T2>
linkedPriQueue2<T1, T2>::linkedPriQueue2(const linkedPriQueue2<T1, T2>& LQ)
{
	Node<Pair<T1, T2>>* NodePtr = LQ.frontPtr;
	Node<Pair<T1, T2>>* backPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = nullptr;
		return;
	}

	//insert the first node
	Node<Pair<T1, T2>>* ptr = new Node<Pair<T1, T2>>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Pair<T1, T2 >* ptr = new Pair<T1, T2>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}