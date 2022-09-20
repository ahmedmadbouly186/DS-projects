#pragma once
#include "Event.h"
class Promotion_event :public Event
{
private:
	/*
	ED is the event day.
	▪ ID is the ID of the mission to be promoted to emergency. This ID must be of a
	*/
public:
	Promotion_event(Marsstation* M_S, int event_day, int id);
	void Execute();

};

