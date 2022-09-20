#include "Marsstation.h"
#include "Event.h"
Event::Event(Marsstation* M_S, int ed, int id)
{
	ED = ed;
	ID = id;
	m_station = M_S;
}
void Event::set_ED(int ED)
{
	ED = ED;
}
void Event::set_ID(int id)
{
	ID = id;
}
int Event::getED() const
{
	return ED;
}
int Event::getid() const
{
	return ID;
}