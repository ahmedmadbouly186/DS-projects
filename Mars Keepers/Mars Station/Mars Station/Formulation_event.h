#pragma once
#include "Event.h"
class Formulation_event :public Event
{
private:
	char TYP;
	int TLOC;
	int MDUR;
	int SIG;
	/*
	TYP is the mission type (M: mountainous, P: polar, E: emergency).
	▪ ED is the event day.
	▪ ID is a unique sequence number that identifies each mission. 
	▪ TLOC is the mission’s target location (in kilometers from the base station).
	▪ MDUR is the number of days needed to fulfill the mission requirements at target location.
	▪ SIG is the mission’s significance.
	*/
public :
	Formulation_event(Marsstation* M_S, char mission_type,int event_day, int id,int  target_location,int mudr,int significance);
	char get_mission_type()const;
	int get_target_location()const;
	int getMDUR()const;
	int get_significance()const;

	void Execute();
};

