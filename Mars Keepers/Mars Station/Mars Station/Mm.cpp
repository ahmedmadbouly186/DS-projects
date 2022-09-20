#include "Mm.h"
#include "MountainousRovers.h"
#include "Marsstation.h"
Mm::Mm():missions(){}
Mm::Mm(Marsstation* M_S,int i, int f, float t, int m, int s) :missions(M_S,i, f, t, m, s) {}
void Mm::assinetorover(Rovers* b) {
	a = b;
}

void Mm::calc_Waiting_Days() {
		Waiting_Days = m_station->getCurent_day() - Formulation_Day;
}

Rovers* Mm::getasassinedrover()
{
	return a;
}
void Mm::reformulate(int FD)
{
	Formulation_Day = FD;
	Execution_Days = -1;
	Completion_Day = -1;
}
Rovers* Mm::clear_rover()
{
	Rovers* temp = a;
	a = nullptr;
	return temp;
}