#include "Formulation_event.h"
#include "Marsstation.h"
#include "Em.h"
#include "Mm.h"
#include "Pm.h"
Formulation_event::Formulation_event(Marsstation* M_S, char mission_type,
	int event_day, int id, int  target_location, int mudr, int significance) :Event(M_S, event_day, id)
{
	TYP = mission_type;
	TLOC = target_location;
	MDUR = mudr;
	SIG = significance;
}


char Formulation_event::get_mission_type()const
{
	return TYP;
}


int Formulation_event::get_target_location()const
{
	return TLOC;
}
int Formulation_event::getMDUR()const
{
	return MDUR;
}
int Formulation_event::get_significance()const
{
	return SIG;
}

void Formulation_event::Execute()
{

	if (TYP == 'E')
	{
		Em* carry_mission=new Em(m_station,ID, ED, TLOC, MDUR, SIG);
		m_station->add_mission(carry_mission);
	}
	else if (TYP == 'M')
	{
		Mm* carry_mission=new Mm(m_station,ID, ED, TLOC, MDUR, SIG);
		m_station->add_mission(carry_mission);

	}
	else if (TYP == 'P')
	{
		Pm* carry_mission=new Pm(m_station,ID, ED, TLOC, MDUR, SIG);
		m_station->add_mission(carry_mission);
	}
}