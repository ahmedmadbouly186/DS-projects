#include "Em.h"
#include "Marsstation.h"
#include "EmergencyRovers.h"
Em::Em() :missions() {}
Em::Em(Marsstation* M_S, int i, int f, float t, int m, int s) : missions(M_S, i, f, t, m, s)
{
	periority = -1 * f + .01 * t + (.1*f + .9) * s + -0.1 * m;
	//the main periority for the significant but FD increase so we need significant get bigger when FD increase 
	//the second periority for the first one come so we want 1 bigger than 2 so we multiply by negative factor
	//the target location we want to small its value as it hasn't periority like significant and FD so we multyply by value bet 0 and 1 
	//we multyply by positive so the furthest has periority higher to assign to the fastest rover
	//duration the one which finish firest assigned firest
}
Rovers* Em::getasassinedrover()
{
	return a;
}
void Em::assinetorover(Rovers* b)
{
	a = b;
}

void Em::calc_Waiting_Days() {
		Waiting_Days = m_station->getCurent_day() - Formulation_Day;
}
float Em::getperiority()
{
	return periority;
}
void Em::reformulate(int FD)
{
	Formulation_Day = FD;
	Execution_Days = -1;
	Completion_Day = -1;
	a = nullptr;
}

Rovers* Em::clear_rover()
{
	Rovers* temp = a;
	a = nullptr;
	return temp;
}