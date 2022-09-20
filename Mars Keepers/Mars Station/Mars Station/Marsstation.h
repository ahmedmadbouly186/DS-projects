#pragma once
#include<fstream>
#include"Event.h"
#include"linkedPriQueue2.h"
#include "ArrayList.h"
#include "Mm.h"
#include "Em.h"
#include "Pm.h"
#include"Check_Up.h"
#include <fstream>
#include <iostream>
#include<string>
#include"ui.h"
class Marsstation
{
	//waiting lists for messions
	linkedPriQueue2<Em*, float> Em_List;
	ArrayList<Mm*> Mm_List;
	LinkedQueue<Pm*> Pm_List;

	linkedPriQueue2<missions*, float> Mission_InEcsution;// list for missions in the excution mode
	ArrayList<missions*>failed_missions; // list for faild miisons we cant assign to the same type of rpvers
	LinkedQueue<missions*> Completed_Mission;// list for completed missions 

	// waiting lists for rovers according to its speed
	linkedPriQueue2<EmergencyRovers*, float> ER_List;
	linkedPriQueue2<MountainousRovers*, float> MR_List;
	linkedPriQueue2<PolarRovers*, float> PR_List;

	linkedPriQueue2<Rovers*, int> Rovers_InMission;//list for rovers in excution mode

	LinkedQueue<Event*> Events;//list for all events


	Check_Up* Maintanance;
	Check_Up* irregular_Maintanance;





	//ifstream InPut;
	//ofstream OutPut;

	ifstream in;
	ui u;
	string filename;
	int rover_id;
	int PROMOTEDM;
	int numberofmissions;
	int mode;

	int PMCOUNT;
	int MMCOUNT;
	int EMCOUNT;

	int AutoP;
	int Curent_Day;
	int NO_mission_checkup;
	int mmcount;
public:
	Marsstation();
	~Marsstation();
	///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void Start();/////////////////////////////////  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	bool IsEnd();////////////////////////////////    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void Assign_Emergency_Missions();///////////      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void Assign_Mountaions_Missions();/////////        \\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void Assign_Polar_Missions();/////////////  FAT HI  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void DestroyMS();////////////////////////            \\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void Increment_WaitingD();//////////////              \\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void AssignFromIRREGULAR();////////////                \\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	//////////////////////////////////////------------------\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;

	///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	bool  add_mission(missions* M);///////////////  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	Mm* Get_M_misiion(int id);///////////////////    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	bool deletemission(int ID);///////////////// ABD  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	int getCurent_day();/////////////////////// HAMED  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	//////////////////////////////////////////----------\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;

	////////////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void Excute_currentday_events();///////////////////////  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void Assign_Faild_missions();/////////////////////////    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void Assign_faild_mission_fromwating(missions*);/////      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void AutoP_Mountaions_Missions();///////////////////        \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void finish_excuting_mission();//////////////////// MAD BULY \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void check_failed_mission(missions*);/////////////            \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	void finish_CHECK_UP();//////////////////////////              \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;
	////////////////////////////////////////////////----------------\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\;


	///////////////////////////////////////////////////////////////////////////////////////////////////\\\\\\\\\\\\\\;
	void getwaiting_mission_id(LinkedQueue<int>& q);//////////////////////////////////////////////////  \\\\\\\\\\\\\\;
	void getInEcsution_id(LinkedQueue<int>& qe, LinkedQueue<int>& qm, LinkedQueue<int>& qp);/////////    \\\\\\\\\\\\\\;
	void getwaiting_rovers_id(LinkedQueue<int>& q);/////////////////////////////////////////////////      \\\\\\\\\\\\\\;
	void get_checkup_rovers(LinkedQueue<int>& q);//////////////////////////////////////////////////        \\\\\\\\\\\\\\;
	void get_irrcheckup_rovers(LinkedQueue<int>& q);//////////////////////////////////////////////          \\\\\\\\\\\\\\;
	void getcompleted_missions(LinkedQueue<int>& qe, LinkedQueue<int>&, LinkedQueue<int>& qp);///            \\\\\\\\\\\\\\;
	void getfailed_missions(LinkedQueue<int>& qe, LinkedQueue<int>& qm, LinkedQueue<int>& qp);//              \\\\\\\\\\\\\\;
	bool checkname();//////////////////////////////////////////////////////////////////////////                \\\\\\\\\\\\\\;
	bool read_data();/////////////////////////////////////////////////////////////////////////                  \\\\\\\\\\\\\\;
	void creat_output();/////////////////////////////////////////////////////////////////////                    \\\\\\\\\\\\\\;
	void print_silentmode();////////////////////////////////////////////////////////////////       HOSNY          \\\\\\\\\\\\\\;
	void print_stepbystepmode();///////////////////////////////////////////////////////////                        \\\\\\\\\\\\\\;
	void print_interactivemode();/////////////////////////////////////////////////////////                          \\\\\\\\\\\\\\;
	void Set_Mode();/////////////////////////////////////////////////////////////////////                            \\\\\\\\\\\\\\;
	void incrementPromoted();///////////////////////////////////////////////////////////                              \\\\\\\\\\\\\\;
	///////////////////////////////////////////////////////////////////////////////////--------------------------------\\\\\\\\\\\\\\;
};


