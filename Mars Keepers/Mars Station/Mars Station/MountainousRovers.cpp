#include "MountainousRovers.h"
MountainousRovers::MountainousRovers():Rovers()
{
}
MountainousRovers::MountainousRovers(int S, int CH, int i) :Rovers( S, CH,i)
{
}

int MountainousRovers::Get_AutoP()
{
	return AutoP;
}

bool MountainousRovers::Get_promoted()
{
	return promoted;
}

void MountainousRovers::set_Get_CheckUpDate(int D)
{
	CheckUpDate = D;
}
int MountainousRovers::GET_No_dayes_of_CheckUp()
{
	return No_dayes_of_CheckUp;
}
int MountainousRovers::Get_CheckUpDate()
{
	return CheckUpDate;
}
int MountainousRovers::Get_No_missions()
{
	return Nunber_missions;
}

int MountainousRovers::Get_Index_Of_Rovers()
{
	return Index_Of_Rovers;
}

float MountainousRovers::Get_speed_of_Rover()
{
	return Speed_Of_Rovers;
}
void MountainousRovers::increment_missions()
{
	Nunber_missions++;
}
void MountainousRovers::clear_missions()
{
	Nunber_missions = 0;
	failed = false;
}
void  MountainousRovers::set_vailed()
{
	failed = true;
}
bool MountainousRovers::get_failed()
{
	return failed;
}
void MountainousRovers::set_NeedMaintance(bool b)
{
	Need_maintanance = b;
}

bool MountainousRovers::get_NeedMaintance()
{
	return Need_maintanance;
}

void MountainousRovers::Set_Speed_of_Rover(float NSpeed)
{
	Speed_Of_Rovers = NSpeed;
}