#pragma once
#include"EmergencyRovers.h"
#include"MountainousRovers.h"
#include"PolarRovers.h"
#include"LinkedQueue.h"
class Marsstation;
class Check_Up
{

	Marsstation* m_station;

	LinkedQueue<EmergencyRovers*> Em_Checks;
	LinkedQueue<MountainousRovers*> Mm_Checks;
	LinkedQueue<PolarRovers*> Pm_Checks;
public:
	Check_Up(Marsstation* M_S);
	void Insert_Rover(EmergencyRovers* RR, int);
	void Insert_Rover(MountainousRovers* RR, int);
	void Insert_Rover(PolarRovers* RR, int);
	bool IS_Empty();
	Rovers* EndOfCheck(bool Force=false);
	~Check_Up();

	void  get_checkup_rovers(LinkedQueue<int>&q);
};

