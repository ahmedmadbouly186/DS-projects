#include "Pm.h"
#include "PolarRovers.h"
#include "Marsstation.h"

Pm::Pm() :missions() {}
Pm::Pm(Marsstation* M_S, int i, int f, float t, int m, int s) : missions(M_S, i, f, t, m, s) {}
void Pm::assinetorover(Rovers* b)
{
	a = b;
}
void Pm::calc_Waiting_Days() {
		Waiting_Days = m_station->getCurent_day() - Formulation_Day;
}
Rovers* Pm::getasassinedrover()
{
	return a;
}
void Pm::reformulate(int FD)
{
	Formulation_Day = FD;
	Execution_Days = -1;
	Completion_Day = -1;
}

Rovers* Pm::clear_rover()
{
	Rovers* temp = a;
	a = nullptr;
	return temp;
}