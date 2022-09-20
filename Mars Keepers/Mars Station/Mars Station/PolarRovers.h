#pragma once
#include"Rovers.h"
class PolarRovers:public Rovers
{
public:
	PolarRovers();
	PolarRovers(int S, int CH, int i);
	virtual int Get_Index_Of_Rovers();
	virtual int Get_CheckUpDate() ;
	virtual void set_Get_CheckUpDate(int CK_date) ;
	virtual int GET_No_dayes_of_CheckUp() ;
	virtual int Get_No_missions() ;
	virtual float Get_speed_of_Rover();
	virtual void increment_missions();
	virtual void clear_missions();
	virtual void set_vailed();
	virtual bool get_failed() ;
	virtual void set_NeedMaintance(bool);
	virtual bool get_NeedMaintance();
	virtual void Set_Speed_of_Rover(float NSpeed);
};

