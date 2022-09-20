#include "PolarRovers.h"
PolarRovers::PolarRovers() :Rovers() 
{
}
PolarRovers::PolarRovers(int S, int CH, int i) : Rovers( S, CH,i)
{
}
void PolarRovers::set_Get_CheckUpDate(int D)
{
	CheckUpDate = D;
}
int PolarRovers::GET_No_dayes_of_CheckUp()
{
	return No_dayes_of_CheckUp;
}
int PolarRovers::Get_CheckUpDate()
{
	return CheckUpDate;
}
int PolarRovers::Get_No_missions()
{
	return Nunber_missions;
}

int PolarRovers::Get_Index_Of_Rovers()
{
	return Index_Of_Rovers;
}

float PolarRovers::Get_speed_of_Rover()
{
	return Speed_Of_Rovers;
}
void PolarRovers::increment_missions()
{
	Nunber_missions++;
}
void PolarRovers::clear_missions()
{
	Nunber_missions = 0;
	failed = false;
}
void  PolarRovers::set_vailed()
{
	failed = true;
}
bool PolarRovers::get_failed()
{
	return failed;
}
void PolarRovers::set_NeedMaintance(bool b)
{
	Need_maintanance = b;
}

bool PolarRovers::get_NeedMaintance()
{
	return Need_maintanance;
}

void PolarRovers::Set_Speed_of_Rover(float NSpeed)
{
	Speed_Of_Rovers = NSpeed;
}