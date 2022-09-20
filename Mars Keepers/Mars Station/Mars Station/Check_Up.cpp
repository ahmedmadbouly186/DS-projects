#include "Check_Up.h"
#include "Marsstation.h"
Check_Up::Check_Up(Marsstation* M_S)
{
	m_station = M_S;
}
void Check_Up::Insert_Rover(EmergencyRovers* RR, int CD)
{
	Em_Checks.enqueue(RR);
	RR->set_Get_CheckUpDate(CD);
}

void Check_Up::Insert_Rover(MountainousRovers* RR, int CD)
{
	Mm_Checks.enqueue(RR);
	RR->set_Get_CheckUpDate(CD);

}

void Check_Up::Insert_Rover(PolarRovers* RR, int CD)
{
	Pm_Checks.enqueue(RR);
	RR->set_Get_CheckUpDate(CD);
}

Rovers* Check_Up::EndOfCheck(bool Force)
{
	if (!Em_Checks.isEmpty())
	{
		EmergencyRovers* Em_Temp;
		Em_Checks.peek(Em_Temp);
		if (Em_Temp->Get_CheckUpDate() + Em_Temp->GET_No_dayes_of_CheckUp() == m_station->getCurent_day() || Force)
		{
			Em_Checks.dequeue(Em_Temp);
			if (Force)
			{
				Em_Temp->Set_Speed_of_Rover(Em_Temp->Get_speed_of_Rover() / 2);
				return Em_Temp;
			}
			return Em_Temp;
		}
	}
	if (!Mm_Checks.isEmpty())
	{
		MountainousRovers* Mm_Temp;
		Mm_Checks.peek(Mm_Temp);
		if (Mm_Temp->Get_CheckUpDate() + Mm_Temp->GET_No_dayes_of_CheckUp() == m_station->getCurent_day() || Force)
		{
			Mm_Checks.dequeue(Mm_Temp);
			if (Force)
			{
				Mm_Temp->Set_Speed_of_Rover(Mm_Temp->Get_speed_of_Rover() / 2);
				return Mm_Temp;
			}
			return Mm_Temp;
		}
	}
	if (!Pm_Checks.isEmpty())
	{
		PolarRovers* Pm_Temp;
		Pm_Checks.peek(Pm_Temp);
		if (Pm_Temp->Get_CheckUpDate() + Pm_Temp->GET_No_dayes_of_CheckUp() == m_station->getCurent_day() || Force)
		{
			Pm_Checks.dequeue(Pm_Temp);
			if (Force)
			{
				Pm_Temp->Set_Speed_of_Rover(Pm_Temp->Get_speed_of_Rover() / 2);
				return Pm_Temp;
			}
			return Pm_Temp;
		}
	}
	return nullptr;
}
void  Check_Up::get_checkup_rovers(LinkedQueue<int> &q)
{
	int x = Em_Checks.getcount() + Mm_Checks.getcount() + Pm_Checks.getcount();
	q.enqueue(x);

	EmergencyRovers* e, * z;
	if (!Em_Checks.isEmpty())
	{

		Em_Checks.dequeue(z);
		Em_Checks.enqueue(z);
		q.enqueue(z->Get_Index_Of_Rovers());
		if (Em_Checks.getcount() > 1)
		{
			do
			{
				Em_Checks.dequeue(e);
				Em_Checks.enqueue(e);
				q.enqueue(e->Get_Index_Of_Rovers());
				Em_Checks.peek(e);

			} while (z != e);
		}
	}
	q.enqueue(0);


	PolarRovers* a, * b;
	if (!Pm_Checks.isEmpty()) {
		Pm_Checks.dequeue(b);
		Pm_Checks.enqueue(b);
		q.enqueue(b->Get_Index_Of_Rovers());
		if (Pm_Checks.getcount() > 1)
		{
			do
			{
				Pm_Checks.dequeue(a);
				Pm_Checks.enqueue(a);
				q.enqueue(a->Get_Index_Of_Rovers());
				Pm_Checks.peek(a);

			} while (b != a);
		}
	}
	q.enqueue(0);


	MountainousRovers* y, * t;
	if (!Mm_Checks.isEmpty()) {
		Mm_Checks.dequeue(y);
		Mm_Checks.enqueue(y);
		q.enqueue(y->Get_Index_Of_Rovers());
		if (Mm_Checks.getcount() > 1)
		{
			do
			{
				Mm_Checks.dequeue(t);
				Mm_Checks.enqueue(t);
				q.enqueue(t->Get_Index_Of_Rovers());
				Mm_Checks.peek(t);

			} while (t != y);
		}
	}
	q.enqueue(0);



}
Check_Up::~Check_Up()
{
	EmergencyRovers* ERtemp;
	while (!Em_Checks.isEmpty())
	{
		Em_Checks.dequeue(ERtemp);
		delete ERtemp;
	}
	MountainousRovers* MRtemp;
	while (!Mm_Checks.isEmpty())
	{
		Mm_Checks.dequeue(MRtemp);
		delete MRtemp;
	}
	PolarRovers* PRtemp;
	while (!Pm_Checks.isEmpty())
	{
		Pm_Checks.dequeue(PRtemp);
		delete PRtemp;
	}
}
bool Check_Up::IS_Empty()
{
	if (Em_Checks.isEmpty() && Mm_Checks.isEmpty() && Pm_Checks.isEmpty())
		return true;
	return false;
}