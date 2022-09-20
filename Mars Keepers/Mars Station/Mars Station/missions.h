#ifndef _MISSION_H
#define _MISSION_H
#include<iostream>
#include "Rovers.h"
using namespace std;
class Marsstation;
class missions
{
protected:
	Marsstation* m_station;
	static int numberofmissions;
	Rovers* a;
	int Formulation_Day;
	float Target_Location;
	int Mission_Duration;
	int Significance;
	int Completion_Day;
	int Execution_Days;
	int Waiting_Days;
	int id;
	bool assigne;
	char type_rover_assigned;
	bool failed;
	int count_fails;
public:
	missions();
	missions(Marsstation* M_S, int i, int f, float t, int m, int s);
	virtual void assinetorover(Rovers* b) = 0;
	virtual Rovers* getasassinedrover()=0;
	virtual Rovers* clear_rover() = 0;
	int get_count_fails();
	void increment_count_fails();
	virtual void calc_Waiting_Days() = 0;
	virtual void reformulate(int FD) = 0;
	void removefromrover();
	void setExecution_Days(int);
	void setCompletion_Day(int);
	void settype_of_rover_assigned(char TYP) { type_rover_assigned = TYP; }
	char gettype_rover_assigned() { return type_rover_assigned; }
	void setfailed(bool x);
	int getid() { return id; }
	bool getassigne() { return assigne; }
	int getWaiting_Days() { return Waiting_Days; }
	int getExecution_Days() { return Execution_Days; }
	int getCompletion_Day() { return Completion_Day; }
	int getFormulation_Day() { return Formulation_Day; }
	int getMission_Duration() { return Mission_Duration; }
	float getTarget_Location() { return Target_Location; }
	int getSignificance() { return Significance; }
	bool isfailed() { return failed; }
	Rovers* getrover() { return a; }
};
#endif
