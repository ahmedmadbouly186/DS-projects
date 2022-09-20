#include "missions.h"
missions::missions() {}
missions::missions(Marsstation* M_S, int i, int f, float t, int m, int s)
{
	m_station = M_S;
	id = i;
	Target_Location = t;
	Significance = s;
	Mission_Duration = m;
	Formulation_Day = f;
	Execution_Days = 0;
	Completion_Day = -1;
	assigne = false;
	failed = false;
	a = nullptr;
	count_fails = 0;
}
void missions::removefromrover() {
	a = nullptr;
}
void missions::setExecution_Days(int ED) {
	Execution_Days = ED;
}
void missions::setCompletion_Day(int CD) {
	Completion_Day = CD;
}
void missions::setfailed(bool x) {
	failed = x;
}

int missions::get_count_fails()
{
	return count_fails;
}
void missions::increment_count_fails()
{
	count_fails++;
}