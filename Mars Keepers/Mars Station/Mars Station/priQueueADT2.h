#pragma once
#include "Pair.h"
template <typename T1, typename T2>
class priQueueADT2
{
public:
	virtual bool isEmpty()const = 0;
	virtual bool enqueue(const Pair<T1, T2>& newentry) = 0;
	virtual bool dequeue(T1& FrontEntry) = 0;
	virtual bool peek(T1& FrontEntry) const = 0;
	virtual ~priQueueADT2() { }

};


