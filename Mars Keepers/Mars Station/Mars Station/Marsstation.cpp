#include "Marsstation.h"
#include"Formulation_event.h"
#include"Promotion_event.h"
#include "EmergencyRovers.h"
#include "MountainousRovers.h"
#include "PolarRovers.h"
#include"Cancellation_event.h"
#include <cmath>
#include <iomanip>
Marsstation::Marsstation() :Curent_Day(0), PROMOTEDM(0), MMCOUNT(0), PMCOUNT(0), EMCOUNT(0)
{
	Maintanance = new Check_Up(this);
	irregular_Maintanance = new Check_Up(this);
	srand(time(NULL));
}
void Marsstation::Start()
{
	Curent_Day++;
	this->Increment_WaitingD();
	this->Excute_currentday_events();
	this->Assign_Faild_missions();
	this->finish_excuting_mission();
	this->finish_CHECK_UP();
	this->AutoP_Mountaions_Missions();
	this->Assign_Emergency_Missions();
	this->AssignFromIRREGULAR();
	this->Assign_Mountaions_Missions();
	this->Assign_Polar_Missions();
	if (mode == 0) {
		this->print_interactivemode();
		if (this->IsEnd()) {
			this->creat_output();
		}
	}
	else if (mode == 1) {
		this->print_stepbystepmode();
		if (this->IsEnd()) {
			this->creat_output();
		}
	}
	else if ((mode == 2) && (this->IsEnd())) {
		this->creat_output();
		this->print_silentmode();
	}
}
void Marsstation::Set_Mode()
{
	u.printmsg("for interactive mode press 0");
	u.printmsg("for step by step mode press 1");
	u.printmsg("for silent mode press 2");
	mode = u.getint();
}
int Marsstation::getCurent_day()
{
	return Curent_Day;
}

bool Marsstation::IsEnd()
{
	if (Events.isEmpty())
		if (Em_List.isEmpty() && Mm_List.isEmpty() && Pm_List.isEmpty() && failed_missions.isEmpty())
			if (Mission_InEcsution.isEmpty())
				if (Maintanance->IS_Empty() && irregular_Maintanance->IS_Empty())
					return true;

	if (Events.isEmpty())
		if ((ER_List.isEmpty() && MR_List.isEmpty() && PR_List.isEmpty()))
			if (Rovers_InMission.isEmpty())
				if (Maintanance->IS_Empty() && irregular_Maintanance->IS_Empty())
					return true;

	if (Events.isEmpty())
		if (Em_List.isEmpty() && Mm_List.isEmpty() && failed_missions.isEmpty() && !Pm_List.isEmpty())
			if (Rovers_InMission.isEmpty() && PR_List.isEmpty())
				if (Maintanance->IS_Empty() && irregular_Maintanance->IS_Empty())
					return true;


	return false;

}

bool Marsstation::deletemission(int ID)
{
	for (int i = 1; i <= Mm_List.getLength(); i++)
	{
		if (Mm_List.getEntry(i)->getid() == ID)
		{
			delete Mm_List.getEntry(i);
			Mm_List.remove(i);
			return true;
		}
	}
	for (int i = 1; i <= failed_missions.getLength(); i++)
	{
		if (failed_missions.getEntry(i)->getid() == ID)
		{
			delete failed_missions.getEntry(i);
			failed_missions.remove(i);
			return true;
		}
	}

	return false;
}
bool  Marsstation::add_mission(missions* M)
{

	Em* EM_temp = dynamic_cast<Em*>(M);
	if (EM_temp)
	{
		Pair<Em*, float> p(EM_temp, EM_temp->getperiority());
		if (!Em_List.enqueue(p))
			return false;
		else
			return true;
	}
	Mm* MM_temp = dynamic_cast<Mm*>(M);
	if (MM_temp)
	{

		if (!(Mm_List.insert(Mm_List.getLength() + 1, MM_temp)))
			return false;
		else
			return true;
	}
	Pm* PM_temp = dynamic_cast<Pm*>(M);
	if (PM_temp)
	{

		if (!(Pm_List.enqueue(PM_temp)))
			return false;
		else
			return true;
	}
}
Mm* Marsstation::Get_M_misiion(int id)
{
	Mm* m = nullptr;
	for (int i = 1; i <= Mm_List.getLength(); i++)
	{
		if (Mm_List.getEntry(i)->getid() == id)
		{
			m = Mm_List.getEntry(i);
			return m;
		}
	}
	for (int i = 1; i <= failed_missions.getLength(); i++)
	{
		if (failed_missions.getEntry(i)->getid() == id)
		{
			m = dynamic_cast<Mm*>(failed_missions.getEntry(i));
			return m;
		}
	}

	return nullptr;
}
void Marsstation::Excute_currentday_events()
{
	Event* e1;
	Events.peek(e1);
	while (!Events.isEmpty() && e1->getED() == Curent_Day)
	{
		e1->Execute();
		Events.dequeue(e1);
		Events.peek(e1);
	}
}
void Marsstation::Assign_Emergency_Missions()
{
	Em* m1;
	bool abeltoAssign = false;
	while (Em_List.peek(m1))
	{
		abeltoAssign = false;
		if (m1->isfailed())
		{
			Em_List.dequeue(m1);
			Assign_faild_mission_fromwating(m1);
		}
		else
		{
			if (!ER_List.isEmpty())
			{
				abeltoAssign = true;
				EmergencyRovers* r1;
				ER_List.dequeue(r1);
				m1->assinetorover(r1);
				m1->settype_of_rover_assigned('E');
			}
			else if (!MR_List.isEmpty())
			{
				abeltoAssign = true;
				MountainousRovers* r1;
				MR_List.dequeue(r1);
				m1->assinetorover(r1);
				m1->settype_of_rover_assigned('M');
			}
			else if (!PR_List.isEmpty())
			{
				abeltoAssign = true;
				PolarRovers* r1;
				PR_List.dequeue(r1);
				m1->assinetorover(r1);
				m1->settype_of_rover_assigned('P');
			}
			else if (m1->getWaiting_Days() >= 5)
			{
				Rovers* Rtemp = irregular_Maintanance->EndOfCheck(1);
				if (Rtemp)
				{
					abeltoAssign = true;
					if (dynamic_cast<EmergencyRovers*>(Rtemp))
					{
						m1->assinetorover(Rtemp);
						m1->settype_of_rover_assigned('E');
					}
					else if (dynamic_cast<MountainousRovers*>(Rtemp))
					{
						m1->assinetorover(Rtemp);
						m1->settype_of_rover_assigned('M');
					}
					else if (dynamic_cast<PolarRovers*>(Rtemp))
					{
						m1->assinetorover(Rtemp);
						m1->settype_of_rover_assigned('P');
					}
				}
			}
			if (abeltoAssign)
			{
				Rovers* r1 = m1->getasassinedrover();
				int excution_dayes; int completed_day; float ED;
				ED = ((m1->getTarget_Location()) * 2 / (r1->Get_speed_of_Rover())) / 25 + m1->getMission_Duration();
				excution_dayes = ceil(ED);
				completed_day = excution_dayes + Curent_Day;
				m1->setExecution_Days(excution_dayes);
				m1->setCompletion_Day(completed_day);

				if (m1->getTarget_Location() >= 700)
				{
					r1->set_NeedMaintance(true);
				}
				float priority = float(1000 * completed_day) + float(.001 * excution_dayes);
				//	m1->calc_Waiting_Days();
				Pair<missions*, float>PM(m1, -priority);
				Pair<Rovers*, int>PR(r1, -completed_day);
				Em_List.dequeue(m1);
				Mission_InEcsution.enqueue(PM);
				Rovers_InMission.enqueue(PR);
				//r1->increment_missions();//////////////////////////////////
			}
			else
			{

				break;
			}
		}
	}
}
void Marsstation::AssignFromIRREGULAR()
{

	bool abeltoAssign = false;
	LinkedQueue<Em*> EmtempQ;
	Em* Etemp;
	while (!Em_List.isEmpty())
	{
		Em_List.dequeue(Etemp);
		EmtempQ.enqueue(Etemp);
	}
	while (!EmtempQ.isEmpty())
	{
		abeltoAssign = false;
		EmtempQ.dequeue(Etemp);
		if (Etemp->isfailed())
		{
			Assign_faild_mission_fromwating(Etemp);
		}
		else
		{
			if (Etemp->getWaiting_Days() >= 5)
			{
				Rovers* Rtemp = irregular_Maintanance->EndOfCheck(1);
				if (Rtemp)
				{
					abeltoAssign = true;
					if (dynamic_cast<EmergencyRovers*>(Rtemp))
					{
						Etemp->assinetorover(Rtemp);
						Etemp->settype_of_rover_assigned('E');
					}
					else if (dynamic_cast<MountainousRovers*>(Rtemp))
					{
						Etemp->assinetorover(Rtemp);
						Etemp->settype_of_rover_assigned('M');
					}
					else if (dynamic_cast<PolarRovers*>(Rtemp))
					{
						Etemp->assinetorover(Rtemp);
						Etemp->settype_of_rover_assigned('P');
					}
				}
			}
		}
		if (abeltoAssign)
		{
			Rovers* r1 = Etemp->getasassinedrover();
			int excution_dayes; int completed_day; float ED;
			ED = ((Etemp->getTarget_Location()) * 2 / (r1->Get_speed_of_Rover())) / 25 + Etemp->getMission_Duration();
			excution_dayes = ceil(ED);
			completed_day = excution_dayes + Curent_Day;
			Etemp->setExecution_Days(excution_dayes);
			Etemp->setCompletion_Day(completed_day);

			if (Etemp->getTarget_Location() >= 700)
			{
				r1->set_NeedMaintance(true);
			}
			float priority = float(1000 * completed_day) + float(.001 * excution_dayes);
			Etemp->calc_Waiting_Days();
			Pair<missions*, float>PM(Etemp, -priority);
			Pair<Rovers*, int>PR(r1, -completed_day);
			Mission_InEcsution.enqueue(PM);
			Rovers_InMission.enqueue(PR);
			//r1->increment_missions();//////////////////////////////////
		}
		else
		{
			add_mission(Etemp);
		}
	}
}
void Marsstation::Assign_Polar_Missions()
{
	Pm* m1;
	bool abeltoAssign = false;

	while (Pm_List.peek(m1))
	{
		abeltoAssign = false;
		if (!PR_List.isEmpty())
		{
			abeltoAssign = true;
			PolarRovers* r1;
			PR_List.dequeue(r1);
			m1->assinetorover(r1);
			m1->settype_of_rover_assigned('P');
		}
		if (abeltoAssign)
		{
			Rovers* r1 = m1->getasassinedrover();
			int excution_dayes; int completed_day; float ED;
			ED = ((m1->getTarget_Location()) * 2 / (r1->Get_speed_of_Rover())) / 25 + m1->getMission_Duration();
			excution_dayes = ceil(ED);
			completed_day = excution_dayes + Curent_Day;
			m1->setExecution_Days(excution_dayes);
			m1->setCompletion_Day(completed_day);

			if (m1->getTarget_Location() >= 700)
			{
				r1->set_NeedMaintance(true);
			}
			float priority = float(1000 * completed_day) + float(.001 * excution_dayes);
			Pair<missions*, float>PM(m1, -priority);
			Pair<Rovers*, int>PR(r1, -completed_day);
			Pm_List.dequeue(m1);
			Mission_InEcsution.enqueue(PM);
			Rovers_InMission.enqueue(PR);
			//r1->increment_missions();///////////////////////////
		}
		else
		{
			break;
		}
	}
}
void Marsstation::Assign_Mountaions_Missions()
{
	Mm* m1;
	bool abeltoAssign = false;
	while (!Mm_List.isEmpty())
	{
		abeltoAssign = false;
		m1 = Mm_List.getEntry(1);
		// if the mission is afaild mission 
		//we assig to arover of the same type
		// if we cant then -> sent to faild listat the end of the list
		if (m1->isfailed())
		{
			Mm_List.remove(1);
			Assign_faild_mission_fromwating(m1);
		}
		else
		{
			if (!MR_List.isEmpty())
			{
				abeltoAssign = true;
				MountainousRovers* r1;
				MR_List.dequeue(r1);
				m1->assinetorover(r1);
				m1->settype_of_rover_assigned('M');
			}
			else if (!ER_List.isEmpty())
			{
				abeltoAssign = true;
				EmergencyRovers* r1;
				ER_List.dequeue(r1);
				m1->assinetorover(r1);
				m1->settype_of_rover_assigned('E');

			}
			if (abeltoAssign)
			{
				Rovers* r1 = m1->getasassinedrover();
				int excution_dayes; int completed_day; float ED;
				ED = ((m1->getTarget_Location()) * 2 / (r1->Get_speed_of_Rover())) / 25 + m1->getMission_Duration();
				excution_dayes = ceil(ED);
				completed_day = excution_dayes + Curent_Day;
				m1->setExecution_Days(excution_dayes);
				m1->setCompletion_Day(completed_day);

				if (m1->getTarget_Location() >= 700)
				{
					r1->set_NeedMaintance(true);
				}
				float priority = float(1000 * completed_day) + float(.001 * excution_dayes);
				Pair<missions*, float>PM(m1, -priority);
				Pair<Rovers*, int>PR(r1, -completed_day);
				Mm_List.remove(1);
				Mission_InEcsution.enqueue(PM);
				Rovers_InMission.enqueue(PR);
				//r1->increment_missions();/////////////////////////////////
			}
			else
			{
				break;
			}
		}

	}
}
void Marsstation::Assign_Faild_missions()
{
	int count = failed_missions.getLength();
	for (int i = 1; i <= failed_missions.getLength(); i++)
	{
		missions* FM = failed_missions.getEntry(i);
		bool find_rover = false;
		if (dynamic_cast<Em*>(FM) && !ER_List.isEmpty())//if the assignd rover was emergency
		{
			find_rover = true;
			EmergencyRovers* R;
			ER_List.dequeue(R);
			FM->assinetorover(R);
		}
		else if (dynamic_cast<Mm*>(FM) && !MR_List.isEmpty())//if the assignd rover was mountainious
		{
			find_rover = true;
			MountainousRovers* R;
			MR_List.dequeue(R);
			FM->assinetorover(R);
		}
		else if (dynamic_cast<Pm*>(FM) && !PR_List.isEmpty())//if the assignd rover was polar
		{
			find_rover = true;
			PolarRovers* R;
			PR_List.dequeue(R);
			FM->assinetorover(R);
		}
		if (find_rover)
		{
			Rovers* R = FM->getasassinedrover();
			int excution_dayes; int completed_day; float ED;
			ED = (((FM->getTarget_Location()) * 2 / (R->Get_speed_of_Rover())) / 25) + FM->getMission_Duration();
			excution_dayes = ceil(ED);
			completed_day = excution_dayes + Curent_Day;
			FM->setExecution_Days(excution_dayes);
			FM->setCompletion_Day(completed_day);
			if (FM->getTarget_Location() >= 700)
			{
				R->set_NeedMaintance(true);
			}
			float priority = float(1000 * completed_day) + float(.001 * excution_dayes);
			Pair<missions*, float>PM(FM, -priority);
			Pair<Rovers*, int>PR(R, -completed_day);
			failed_missions.remove(i--);
			//after remove this mission from the list 
			//we should check again in the same position 
			// because array list will shift the data to the lift
			//and there will be new mession on this position
			Mission_InEcsution.enqueue(PM);
			Rovers_InMission.enqueue(PR);
			R->increment_missions();

		}
	}
}
void Marsstation::Assign_faild_mission_fromwating(missions* FM)
{
	bool abelToAssign = false;
	if (dynamic_cast<Em*>(FM) && !ER_List.isEmpty())
	{
		abelToAssign = true;
		EmergencyRovers* R;
		ER_List.dequeue(R);
		FM->assinetorover(R);
	}
	else if (dynamic_cast<Mm*>(FM) && !MR_List.isEmpty())
	{
		abelToAssign = true;
		MountainousRovers* R;
		MR_List.dequeue(R);
		FM->assinetorover(R);
	}
	else if (dynamic_cast<Pm*>(FM) && !PR_List.isEmpty())
	{
		abelToAssign = true;
		PolarRovers* R;
		PR_List.dequeue(R);
		FM->assinetorover(R);
	}
	if (abelToAssign)
	{
		Rovers* R = FM->getasassinedrover();
		int excution_dayes; int completed_day; float ED;
		ED = ((FM->getTarget_Location()) * 2 / (R->Get_speed_of_Rover())) / 25 + FM->getMission_Duration();
		excution_dayes = ceil(ED);
		completed_day = excution_dayes + Curent_Day;
		FM->setExecution_Days(excution_dayes);
		FM->setCompletion_Day(completed_day);
		if (FM->getTarget_Location() >= 700)
		{
			R->set_NeedMaintance(true);
		}
		float priority = float(1000 * completed_day) + float(.001 * excution_dayes);
		Pair<missions*, float>PM(FM, -priority);
		Pair<Rovers*, int>PR(R, -completed_day);
		Mission_InEcsution.enqueue(PM);
		Rovers_InMission.enqueue(PR);
		R->increment_missions();
	}
	else
	{
		int index = failed_missions.getLength();
		failed_missions.insert(index + 1, FM);
	}
}
void Marsstation::AutoP_Mountaions_Missions()
{
	while (!Mm_List.isEmpty())
	{
		Mm* m1;
		m1 = Mm_List.getEntry(1);
		int wating_days = Curent_Day - m1->getFormulation_Day();
		if (wating_days >= AutoP)
		{
			Promotion_event p1(this, Curent_Day, m1->getid());
			p1.Execute();
			this->incrementPromoted();

		}
		else
		{
			break;
		}
	}
	for (int i = 1; i <= failed_missions.getLength(); i++)
	{
		Mm* m1 = dynamic_cast <Mm*>(failed_missions.getEntry(i));
		if (m1)
		{
			int wating_days = Curent_Day - m1->getFormulation_Day();
			if (wating_days >= AutoP)
			{
				Promotion_event p1(this, Curent_Day, m1->getid());
				p1.Execute();
				this->incrementPromoted();
			}
		}
	}
}
void Marsstation::finish_excuting_mission()
{
	int count = 0;
	missions* m1;
	while (Mission_InEcsution.peek(m1))
	{
		if (m1->getCompletion_Day() == Curent_Day)
		{
			count++;
			Mission_InEcsution.dequeue(m1);
			this->check_failed_mission(m1);
			if (!m1->isfailed())// if Succeed mission
			{
				Completed_Mission.enqueue(m1);
				m1->getasassinedrover()->increment_missions();
			}
			else// if failed mission
			{
				m1->getasassinedrover()->set_vailed();
				m1->reformulate(Curent_Day);
				this->add_mission(m1);
				m1->clear_rover();
			}
		}
		else
		{
			break;
		}
	}
	for (int i = 0; i < count; i++)
	{
		Rovers* R;
		Rovers_InMission.dequeue(R);
		if (R->Get_No_missions() == NO_mission_checkup || R->get_failed())
		{
			if (dynamic_cast<EmergencyRovers*>(R))
			{
				EmergencyRovers* r1 = dynamic_cast<EmergencyRovers*>(R);
				r1->clear_missions();
				Maintanance->Insert_Rover(r1, Curent_Day);
			}
			else if (dynamic_cast<MountainousRovers*>(R))
			{
				MountainousRovers* r1 = dynamic_cast<MountainousRovers*>(R);
				r1->clear_missions();
				Maintanance->Insert_Rover(r1, Curent_Day);
			}
			else
			{
				PolarRovers* r1 = dynamic_cast<PolarRovers*>(R);
				r1->clear_missions();
				Maintanance->Insert_Rover(r1, Curent_Day);
			}
			R->set_NeedMaintance(false);
		}
		else if (R->get_NeedMaintance())
		{
			if (dynamic_cast<EmergencyRovers*>(R))
			{
				EmergencyRovers* r1 = dynamic_cast<EmergencyRovers*>(R);
				irregular_Maintanance->Insert_Rover(r1, Curent_Day);
			}
			else if (dynamic_cast<MountainousRovers*>(R))
			{
				MountainousRovers* r1 = dynamic_cast<MountainousRovers*>(R);
				irregular_Maintanance->Insert_Rover(r1, Curent_Day);
			}
			else
			{
				PolarRovers* r1 = dynamic_cast<PolarRovers*>(R);
				irregular_Maintanance->Insert_Rover(r1, Curent_Day);
			}
			R->set_NeedMaintance(false);
		}
		else
		{
			if (dynamic_cast<EmergencyRovers*>(R))
			{
				EmergencyRovers* r1 = dynamic_cast<EmergencyRovers*>(R);
				Pair< EmergencyRovers*, float>p1(r1, r1->Get_speed_of_Rover());
				ER_List.enqueue(p1);
			}
			else if (dynamic_cast<MountainousRovers*>(R))
			{
				MountainousRovers* r1 = dynamic_cast<MountainousRovers*>(R);
				Pair< MountainousRovers*, float>p1(r1, r1->Get_speed_of_Rover());
				MR_List.enqueue(p1);
			}
			else
			{
				PolarRovers* r1 = dynamic_cast<PolarRovers*>(R);
				Pair< PolarRovers*, float>p1(r1, r1->Get_speed_of_Rover());
				PR_List.enqueue(p1);
			}
		}

	}
}
void Marsstation::check_failed_mission(missions* m)
{
	Rovers* R = m->getasassinedrover();
	double randm = ((double)rand() / (RAND_MAX));
	double limit = 0;

	if (dynamic_cast<EmergencyRovers*>(R) && dynamic_cast<Em*>(m))
	{
		limit += .05;
	}
	else if (dynamic_cast<MountainousRovers*>(R) && dynamic_cast<Mm*>(m))
	{
		limit += .05;
	}
	else if (dynamic_cast<Pm*>(m))
	{
		limit += .05;
	}
	else
	{
		limit += .1;
	}
	limit += m->getTarget_Location() / 100 / 100;
	limit = limit / pow(2, m->get_count_fails());
	if (randm > 0 && randm < limit)
	{
		m->increment_count_fails();
		m->setfailed(true);
	}
	else
	{
		m->setfailed(false);

	}
}
void Marsstation::finish_CHECK_UP()
{
	Rovers* R = Maintanance->EndOfCheck();
	while (R)
	{
		if (dynamic_cast<EmergencyRovers*>(R))
		{
			EmergencyRovers* r = dynamic_cast<EmergencyRovers*>(R);
			Pair<EmergencyRovers*, float>p(r, r->Get_speed_of_Rover());
			ER_List.enqueue(p);
		}
		else if (dynamic_cast<MountainousRovers*>(R))
		{
			MountainousRovers* r = dynamic_cast<MountainousRovers*>(R);
			Pair<MountainousRovers*, float>p(r, r->Get_speed_of_Rover());
			MR_List.enqueue(p);
		}
		else
		{
			PolarRovers* r = dynamic_cast<PolarRovers*>(R);
			Pair<PolarRovers*, float>p(r, r->Get_speed_of_Rover());
			PR_List.enqueue(p);
		}
		R = Maintanance->EndOfCheck();
	}
	R = irregular_Maintanance->EndOfCheck();
	while (R)
	{
		if (dynamic_cast<EmergencyRovers*>(R))
		{
			EmergencyRovers* r = dynamic_cast<EmergencyRovers*>(R);
			Pair<EmergencyRovers*, float>p(r, r->Get_speed_of_Rover());
			ER_List.enqueue(p);
		}
		else if (dynamic_cast<MountainousRovers*>(R))
		{
			MountainousRovers* r = dynamic_cast<MountainousRovers*>(R);
			Pair<MountainousRovers*, float>p(r, r->Get_speed_of_Rover());
			MR_List.enqueue(p);
		}
		else
		{
			PolarRovers* r = dynamic_cast<PolarRovers*>(R);
			Pair<PolarRovers*, float>p(r, r->Get_speed_of_Rover());
			PR_List.enqueue(p);
		}
		R = irregular_Maintanance->EndOfCheck();
	}

}



void Marsstation::DestroyMS()
{
	missions* Mtemp;
	while (!Completed_Mission.isEmpty())
	{
		Completed_Mission.dequeue(Mtemp);
		delete Mtemp;
	}
	EmergencyRovers* ERtemp;
	while (!ER_List.isEmpty())
	{
		ER_List.dequeue(ERtemp);
		delete ERtemp;
	}
	MountainousRovers* MRtemp;
	while (!MR_List.isEmpty())
	{
		MR_List.dequeue(MRtemp);
		delete MRtemp;
	}
	PolarRovers* PRtemp;
	while (!PR_List.isEmpty())
	{
		PR_List.dequeue(PRtemp);
		delete PRtemp;
	}
	delete Maintanance;
	delete irregular_Maintanance;
}

void Marsstation::Increment_WaitingD()
{
	LinkedQueue<Em*> EMtemp;
	Em* ETemp;
	while (!Em_List.isEmpty())
	{
		Em_List.dequeue(ETemp);
		ETemp->calc_Waiting_Days();
		EMtemp.enqueue(ETemp);
	}
	while (!EMtemp.isEmpty())
	{
		EMtemp.dequeue(ETemp);
		add_mission(ETemp);
	}


	LinkedQueue<Mm*> MMtemp;
	Mm* MTemp;
	while (!Mm_List.isEmpty())
	{
		MTemp = Mm_List.getEntry(1);
		Mm_List.remove(1);
		MTemp->calc_Waiting_Days();
		MMtemp.enqueue(MTemp);
	}
	while (!MMtemp.isEmpty())
	{
		MMtemp.dequeue(MTemp);
		add_mission(MTemp);
	}


	LinkedQueue<Pm*> PMtemp;
	Pm* PTemp;
	while (!Pm_List.isEmpty())
	{
		Pm_List.dequeue(PTemp);
		PTemp->calc_Waiting_Days();
		PMtemp.enqueue(PTemp);
	}
	while (!PMtemp.isEmpty())
	{
		PMtemp.dequeue(PTemp);
		add_mission(PTemp);
	}

	for (int i = 1; i <= failed_missions.getLength(); i++)
	{
		failed_missions.getEntry(i)->calc_Waiting_Days();
	}

}

Marsstation::~Marsstation()
{
	DestroyMS();
}







bool Marsstation::checkname() {
	filename = u.getfilename();
	in.open(filename);
	if (!in.is_open()) {
		u.invalid();
		return false;
	}
	return true;
}
bool Marsstation::read_data()
{
	int  NM, NP, NE, CM, CP, CE, NUMBEROFEVENTS;
	char type, MISSION;
	int ED, ID, TLOC, MDUR, SIG;
	int* SER = NULL;
	int* SMR = NULL;
	int* SPR = NULL;
	//int ID2 = -1;
	ID = 0;
	int i = 0;
	string line;
	bool flage = checkname();
	if (flage)
	{

		while (!in.eof())
		{

			if (i > 5)
			{
				in >> type;

				if (type == 'F') {
					in >> MISSION >> ED >> ID >> TLOC >> MDUR >> SIG;

					Formulation_event* x = new Formulation_event(this, MISSION, ED, ID, TLOC, MDUR, SIG);
					Events.enqueue(x);
					if (MISSION == 'M')
					{
						MMCOUNT++;
					}
				}
				else if (type == 'P') {
					in >> ED >> ID;
					Promotion_event* x = new Promotion_event(this, ED, ID);
					Events.enqueue(x);
				}
				else {
					in >> ED >> ID;
					Cancellation_event* x = new Cancellation_event(this, ED, ID);
					Events.enqueue(x);
				}
				if (i == (NUMBEROFEVENTS + 5))break;

			}
			else if (i == 2)
			{
				in >> NE;
				SER = new int[NE];
				for (int j = 0; j < NE; j++)
				{
					in >> SER[j];
				}
			}
			else if (i == 1) {
				in >> NP;
				SPR = new int[NP];
				for (int j = 0; j < NP; j++)
				{
					in >> SPR[j];
				}
			}
			else if (i == 0) {
				in >> NM;
				SMR = new int[NM];
				for (int j = 0; j < NM; j++)
				{
					in >> SMR[j];
				}
			}
			else if (i == 3) {
				in >> NO_mission_checkup >> CM >> CP >> CE;
			}
			else if (i == 4) {
				in >> AutoP;
			}
			else if (i == 5) {
				in >> NUMBEROFEVENTS;
			}
			i++;
			//getline(in, line);
		}
		in.close();


		///////////////////creat rovers/////////////////// 
		rover_id = 0;
		for (int i = 0; i < NM; i++) {
			rover_id++;
			if (SMR[i] == 0)continue;
			MountainousRovers* x = new MountainousRovers(SMR[i], CM, rover_id);
			Pair<MountainousRovers*, float >z(x, SMR[i]);
			MR_List.enqueue(z);

		}
		for (int i = 0; i < NP; i++) {
			rover_id++;
			if (SPR[i] == 0)continue;
			PolarRovers* x = new PolarRovers(SPR[i], CP, rover_id);
			Pair<PolarRovers*, float >z(x, SPR[i]);
			PR_List.enqueue(z);

		}
		for (int i = 0; i < NE; i++) {
			rover_id++;
			if (SER[i] == 0)continue;
			EmergencyRovers* x = new EmergencyRovers(SER[i], CE, rover_id);
			Pair<EmergencyRovers*, float >z(x, SER[i]);
			ER_List.enqueue(z);

		}



	}
	return flage;
}


void  Marsstation::creat_output() {
	ofstream f;
	int failed_count = 0;
	numberofmissions = 0;
	float AvgWait = 0.0;
	float AvgExec = 0.0;
	filename = u.getfilename() + ".txt";
	f.open(filename);
	if (f.is_open()) {
		f << "CD" << "\t" << "ID" << "\t" << "FD" << "\t" << "WD" << "\t" << "ED" << endl;
		while (!Completed_Mission.isEmpty()) {
			missions* x;
			Completed_Mission.dequeue(x);
			int factor = 1;
			if (x->get_count_fails() > 0)
			{
				factor = -1;
				failed_count++;
			}
			f << x->getCompletion_Day() << "\t" << x->getid() * factor << "\t" << x->getFormulation_Day() << "\t" << x->getWaiting_Days() << "\t" << x->getExecution_Days() << endl;
			numberofmissions++;
			AvgWait += x->getWaiting_Days();
			AvgExec += x->getExecution_Days();
			if (dynamic_cast<Em*>(x)) { EMCOUNT++; }
			if (dynamic_cast<Pm*>(x)) { PMCOUNT++; }
			if (dynamic_cast<Mm*>(x)) { mmcount++; }
		}
		if (numberofmissions == 0)
		{
			AvgWait = 0;
			AvgExec = 0;
		}
		else
		{
			AvgWait = AvgWait / numberofmissions;
			AvgExec = AvgExec / numberofmissions;
		}
		f << "Missons: " << numberofmissions << " [ " << "M: " << mmcount << ", P: " << PMCOUNT << ", E: " << EMCOUNT << "]" << endl;
		f << "Rovers: " << ER_List.getcount() + PR_List.getcount() + MR_List.getcount() << "[ M:" << MR_List.getcount() << ", P: " << PR_List.getcount() << " , E: " << ER_List.getcount() << "]" << endl;
		f << "Avg Wait = " << AvgWait << ", Avg Exec = " << AvgExec << endl;
		if (MMCOUNT == 0)
		{
			f << "Auto-promoted: " << "0" << "%" << endl;
		}
		else
		{
			f << "Auto-promoted: " << ((float)PROMOTEDM / MMCOUNT) * 100 << "%" << endl;
		}
		f << "Failed Missions: " << failed_count << endl;
		f.close();
	}
	else {
		u.invalid();
	}
}

void Marsstation::print_silentmode() {
	u.silentmode();
}
void Marsstation::print_stepbystepmode() {
	u.stepbystepmode(this);


}
void Marsstation::print_interactivemode() {
	u.interactivemode(this);
}


void Marsstation::getwaiting_mission_id(LinkedQueue<int>& q)
{
	int x = Em_List.getcount() + Mm_List.getLength() + Pm_List.getcount() + failed_missions.getLength();
	q.enqueue(x);
	Em* e, * z;
	LinkedQueue<Em*>etemp;
	while (!Em_List.isEmpty())
	{
		Em_List.dequeue(z);
		etemp.enqueue(z);
		int factor1 = 1;
		if (z->get_count_fails() > 0)factor1 = -1;
		q.enqueue(z->getid() * factor1);
	}
	while (!etemp.isEmpty())
	{
		etemp.dequeue(z);
		this->add_mission(z);
	}
	for (int i = 1; i <= failed_missions.getLength(); i++)
	{
		Em* m1 = dynamic_cast <Em*>(failed_missions.getEntry(i));
		if (m1)
		{
			int factor = 1;
			if (m1->get_count_fails() > 0)factor = -1;
			q.enqueue(m1->getid() * factor);
		}
	}
	q.enqueue(0);
	////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	Pm* a, * b;
	if (!Pm_List.isEmpty())
	{

		Pm_List.dequeue(b);
		Pm_List.enqueue(b);

		int factor1 = 1;
		if (b->get_count_fails() > 0)factor1 = -1;

		q.enqueue(b->getid() * factor1);
		if (Pm_List.getcount() > 1)
		{
			do
			{
				Pm_List.dequeue(a);
				Pm_List.enqueue(a);

				int factor2 = 1;
				if (a->get_count_fails() > 0)factor2 = -1;

				q.enqueue(a->getid() * factor2);
				Pm_List.peek(a);

			} while (b != a);
		}
	}
	for (int i = 1; i <= failed_missions.getLength(); i++)
	{
		Pm* mp = dynamic_cast <Pm*>(failed_missions.getEntry(i));
		if (mp)
		{
			int factor = 1;
			if (mp->get_count_fails() > 0)factor = -1;
			q.enqueue(mp->getid() * factor);
		}
	}
	q.enqueue(0);

	////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////
	int i = 1;
	while (i <= Mm_List.getLength())
	{
		Mm* x;
		x = Mm_List.getEntry(i);
		int factor = 1;
		if (x->get_count_fails() > 0)factor = -1;
		q.enqueue(x->getid() * factor);
		i++;
	}
	for (int j = 1; j <= failed_missions.getLength(); j++)
	{
		Mm* mm = dynamic_cast <Mm*>(failed_missions.getEntry(j));
		if (mm)
		{
			int factor = 1;
			if (mm->get_count_fails() > 0)factor = -1;
			q.enqueue(mm->getid() * factor);
		}
	}
	q.enqueue(0);

}
void Marsstation::getInEcsution_id(LinkedQueue<int>& qe, LinkedQueue<int>& qm, LinkedQueue<int>& qp)
{

	int x;
	LinkedQueue<missions*> temp;
	x = Mission_InEcsution.getcount();
	qe.enqueue(x);
	missions* z;
	while (!Mission_InEcsution.isEmpty()) {
		Mission_InEcsution.dequeue(z);
		temp.enqueue(z);
	}
	while (!temp.isEmpty()) {


		temp.dequeue(z);


		int excution_dayes; int completed_day; float ED;
		ED = ((z->getTarget_Location()) * 2 / (z->getrover()->Get_speed_of_Rover())) / 25 + z->getMission_Duration();
		excution_dayes = ceil(ED);
		completed_day = excution_dayes + z->getWaiting_Days() + z->getFormulation_Day();
		z->setExecution_Days(excution_dayes);
		z->setCompletion_Day(completed_day);


		float priority = float(1000 * completed_day) + float(.001 * excution_dayes);
		Pair<missions*, float>PM(z, -priority);




		Mission_InEcsution.enqueue(PM);
		if (dynamic_cast<Em*>(z)) {
			qe.enqueue(z->getid());
			qe.enqueue(z->getrover()->Get_Index_Of_Rovers());
		}
		else if (dynamic_cast<Mm*>(z)) {
			qm.enqueue(z->getid());
			qm.enqueue(z->getrover()->Get_Index_Of_Rovers());
		}
		else {
			qp.enqueue(z->getid());
			qp.enqueue(z->getrover()->Get_Index_Of_Rovers());
		}
	}
}
void Marsstation::getwaiting_rovers_id(LinkedQueue<int>& q) {
	int x = ER_List.getcount() + MR_List.getcount() + PR_List.getcount();
	q.enqueue(x);
	EmergencyRovers* e;
	LinkedQueue<EmergencyRovers*> temp;
	while (!ER_List.isEmpty()) {
		ER_List.dequeue(e);
		temp.enqueue(e);
	}
	while (!temp.isEmpty())
	{
		temp.dequeue(e);
		Pair<EmergencyRovers*, float> z(e, e->Get_speed_of_Rover());
		ER_List.enqueue(z);
		q.enqueue(e->Get_Index_Of_Rovers());
	}
	q.enqueue(0);


	PolarRovers* a;
	LinkedQueue<PolarRovers*> temp1;
	while (!PR_List.isEmpty()) {
		PR_List.dequeue(a);
		temp1.enqueue(a);
	}
	while (!temp1.isEmpty())
	{
		temp1.dequeue(a);
		Pair<PolarRovers*, float> z(a, a->Get_speed_of_Rover());
		PR_List.enqueue(z);
		q.enqueue(a->Get_Index_Of_Rovers());
	}
	q.enqueue(0);


	MountainousRovers* y;
	LinkedQueue<MountainousRovers*> temp2;
	while (!MR_List.isEmpty()) {
		MR_List.dequeue(y);
		temp2.enqueue(y);
	}
	while (!temp2.isEmpty())
	{
		temp2.dequeue(y);
		Pair<MountainousRovers*, int> z(y, y->Get_speed_of_Rover());
		MR_List.enqueue(y);
		q.enqueue(y->Get_Index_Of_Rovers());
	}
	q.enqueue(0);



}
void Marsstation::get_checkup_rovers(LinkedQueue<int>& q) {
	Maintanance->get_checkup_rovers(q);
}
void Marsstation::get_irrcheckup_rovers(LinkedQueue<int>& q)
{
	irregular_Maintanance->get_checkup_rovers(q);
}

void  Marsstation::getcompleted_missions(LinkedQueue<int>& qe, LinkedQueue<int>& qm, LinkedQueue<int>& qp) {
	int x;
	x = Completed_Mission.getcount();
	qe.enqueue(x);
	missions* e, * z;
	if (!Completed_Mission.isEmpty()) {

		Completed_Mission.dequeue(z);
		Completed_Mission.enqueue(z);
		if (Curent_Day == 31) {
			int x = 0;
			x++;
		}
		if (z->getCompletion_Day() == Curent_Day)
		{
			int factor = 1;
			if (z->get_count_fails() > 0)factor = -1;

			if (dynamic_cast<Em*>(z)) {
				qe.enqueue(z->getid() * factor);
			}
			else if (dynamic_cast<Mm*>(z)) {
				qm.enqueue(z->getid() * factor);
			}
			else {
				qp.enqueue(z->getid() * factor);
			}


		}
		if (Completed_Mission.getcount() > 1)
		{
			do
			{
				Completed_Mission.dequeue(e);
				Completed_Mission.enqueue(e);
				if (e->getCompletion_Day() == Curent_Day)
				{
					int factor = 1;
					if (e->get_count_fails() > 0)factor = -1;

					if (dynamic_cast<Em*>(e)) {
						qe.enqueue(e->getid() * factor);
					}
					else if (dynamic_cast<Mm*>(e)) {
						qm.enqueue(e->getid() * factor);
					}
					else {
						qp.enqueue(e->getid() * factor);
					}
				}
				Completed_Mission.peek(e);

			} while (z != e);
		}
	}
}

void Marsstation::getfailed_missions(LinkedQueue<int>& qe, LinkedQueue<int>& qm, LinkedQueue<int>& qp) {
	int x;
	missions* e;
	x = failed_missions.getLength();
	qe.enqueue(x);
	for (int i = 1; i <= failed_missions.getLength(); i++)
	{
		e = failed_missions.getEntry(i);
		if (dynamic_cast<Em*>(e))
		{
			x = e->getid() * -1;
			qe.enqueue(x);
		}
		else if (dynamic_cast<Mm*>(e))
		{
			x = e->getid() * -1;
			qm.enqueue(x);
		}
		else if (dynamic_cast<Pm*>(e))
		{
			x = e->getid() * -1;
			qp.enqueue(x);
		}
	}
}

void Marsstation::incrementPromoted()
{
	PROMOTEDM++;
}
