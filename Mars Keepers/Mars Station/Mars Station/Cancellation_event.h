#pragma once
#include "Event.h"
class Cancellation_event :public Event
{
private:
public:

	Cancellation_event(Marsstation* M_S,int event_day,int id);
	
	void Execute();

};

