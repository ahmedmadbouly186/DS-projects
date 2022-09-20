#pragma once
#include "missions.h"
#include "Rovers.h"
class Mm :public missions
{
public:
	Mm();
	Mm(Marsstation* M_S,int i, int f, float t, int m, int s);
	virtual void assinetorover(Rovers* b);
	virtual Rovers* getasassinedrover();
	virtual void calc_Waiting_Days() ;
	virtual void reformulate(int FD) ;
	virtual Rovers* clear_rover() ;

};

