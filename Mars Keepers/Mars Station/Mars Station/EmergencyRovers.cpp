#include "EmergencyRovers.h"
EmergencyRovers::EmergencyRovers():Rovers()
{
}
EmergencyRovers::EmergencyRovers(int S, int CH, int i) :Rovers(S,CH,i)
{
}

void EmergencyRovers::set_Get_CheckUpDate(int D)
{
	CheckUpDate = D;
}
int EmergencyRovers::GET_No_dayes_of_CheckUp()
{
	return No_dayes_of_CheckUp;
}
int EmergencyRovers::Get_CheckUpDate()
{
	return CheckUpDate;
}
int EmergencyRovers::Get_No_missions()
{
	return Nunber_missions;
}
int EmergencyRovers::Get_Index_Of_Rovers()
{
	return Index_Of_Rovers;
}

float EmergencyRovers::Get_speed_of_Rover()
{
	return Speed_Of_Rovers;
}

void EmergencyRovers::increment_missions()
{
	Nunber_missions++;
}
void EmergencyRovers::clear_missions()
{
	Nunber_missions = 0;
	failed = false;
}
void  EmergencyRovers::set_vailed()
{
	failed = true;
}
bool EmergencyRovers::get_failed()
{
	return failed;
}
void EmergencyRovers::set_NeedMaintance(bool b)
{
	Need_maintanance = b;
}

bool EmergencyRovers::get_NeedMaintance()
{
	return Need_maintanance;
}

void EmergencyRovers::Set_Speed_of_Rover(float NSpeed)
{
	Speed_Of_Rovers = NSpeed;
}