#pragma once
#include "missions.h"
class Pm :public missions
{
public:
	Pm();
	Pm(Marsstation* M_S,int i, int f, float t, int m, int s);
	virtual void assinetorover(Rovers* b);
	virtual Rovers* getasassinedrover();
	virtual void calc_Waiting_Days() ;
	virtual void reformulate(int FD) ;
	virtual Rovers* clear_rover() ;


};

