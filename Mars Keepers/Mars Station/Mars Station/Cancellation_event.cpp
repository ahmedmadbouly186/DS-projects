#include "Cancellation_event.h"
#include "Marsstation.h"
Cancellation_event::Cancellation_event(Marsstation* M_S, int event_day, int id) :Event(M_S, event_day, id)
{
}


void Cancellation_event::Execute()
{
	m_station->deletemission(ID);
}