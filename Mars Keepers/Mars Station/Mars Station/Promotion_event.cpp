#include "Promotion_event.h"
#include "Marsstation.h"
#include "Em.h"
#include "Mm.h"
Promotion_event::Promotion_event(Marsstation* M_S, int event_day, int id) :Event(M_S, event_day, id)
{
}



void Promotion_event::Execute()
{
	//(ID, ED, TLOC, MDUR, SIG)
	Mm* carry_del_mission = m_station->Get_M_misiion(ID);
	if (carry_del_mission)
	{
		int TLOC = carry_del_mission->getTarget_Location();
		int MDUR = carry_del_mission->getMission_Duration();
		int SIG = carry_del_mission->getSignificance();
		Em* carry_new_mession=new Em(m_station,ID, carry_del_mission->getFormulation_Day(), TLOC, MDUR, SIG);
		carry_new_mession->calc_Waiting_Days();
		m_station->deletemission(ID);
		m_station->add_mission(carry_new_mession);
	}
	
}