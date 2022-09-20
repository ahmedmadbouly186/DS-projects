#pragma once
#pragma once
template <class T1, class T2>
class Pair
{
private:
	T1 Item;
	T2 Priority;
public:
    Pair()
	{
		Priority = -1;
	}
	
	Pair(const T1& r_Item)
	{
		Item = r_Item;
		Priority = -1;
	}
	Pair(const T1& r_Item, T2 p)
	{
		Item = r_Item;
		Priority = p;
	}
	Pair(const Pair<T1, T2>& cp)
	{
		Item = cp.getItem();
		Priority = cp.getPriority();
	}


	void setpair(T1 i, T2 p)
	{
		Item = i;
		Priority = p;
	}
	T1 getItem() const
	{
		return Item;
	}
	T2 getPriority() const
	{
		return Priority;
	}

	bool operator < (Pair<T1, T2>p)
	{
		return (Priority < p.Priority);
	}
	bool operator > (Pair<T1, T2>p)
	{
		return (Priority > p.Priority);
	}
	bool operator ==(Pair<T1, T2>p)
	{
		return (Priority == p.Priority);
	}
	bool operator <=(Pair<T1, T2>p)
	{
		return (Priority <= p.Priority);
	}
	bool operator >=(Pair<T1, T2>p)
	{
		return (Priority >= p.Priority);
	}

};



