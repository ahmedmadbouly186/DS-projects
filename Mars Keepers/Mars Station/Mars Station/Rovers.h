#pragma once
class Rovers
{
protected:
	int Index_Of_Rovers;
	float Speed_Of_Rovers;
	int CheckUpDate;
	int No_dayes_of_CheckUp;
	int Nunber_missions;
	bool failed;
	bool Need_maintanance;//if the mission was needs a lot of days it will go to irregualr maintance
public:
	Rovers();
	Rovers(float S, int CH,int i);
	virtual int Get_Index_Of_Rovers()=0 ;
	virtual int Get_CheckUpDate()= 0 ;
	virtual int Get_No_missions() = 0;
	virtual void set_Get_CheckUpDate(int CK_date) = 0;
	virtual int GET_No_dayes_of_CheckUp() = 0;
	virtual float Get_speed_of_Rover()=0 ;
	virtual void increment_missions()=0;
	virtual void clear_missions() = 0;
	virtual void set_vailed() = 0;
	virtual bool get_failed() = 0;
	virtual void set_NeedMaintance(bool) = 0;
	virtual bool get_NeedMaintance() = 0;
	virtual void Set_Speed_of_Rover(float NSpeed) = 0;
	  
};

