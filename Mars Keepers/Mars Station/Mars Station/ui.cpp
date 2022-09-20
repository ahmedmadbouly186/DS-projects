#include "ui.h"
#include"Marsstation.h"
#include<Windows.h>
#include<iomanip>
#include<conio.h>
#include<stdio.h>
string ui::getfilename()
{

	printmsg("please enter file name ");
	cin >> filename;
	return filename;
}

void ui::silentmode() {
	cout << "Silent Mode" << endl;
	cout << "Simulation Starts..." << endl;
	cout << "Simulation ends, Output file created" << endl;
}
void ui::stepbystepmode(Marsstation* m) 
{
		print(m);
		Sleep(1000);
}
void ui::print(Marsstation* m){
	cout << "Curent Day: " << m->getCurent_day() << endl;
	print_line1(m, 0);
	cout << "------------------------------------------" << endl;
	print_line2(m);
	cout << "------------------------------------------" << endl;
	print_line1(m, 1);
	cout << "------------------------------------------" << endl;
	print_line1(m, 2);
	cout << "------------------------------------------" << endl;
	print_line1(m, 3);
	cout << "------------------------------------------" << endl;
	print_line5(m,0);
	cout << endl;
}
void ui::interactivemode(Marsstation* m) {
	int c;
	cout << "to print current day press enter to skip press any key" << endl;
	c = _getch();
	if (c == 13) {
		print(m);
		cout << endl;
	}
}


void ui::print_line1(Marsstation* m, int i)
{
	LinkedQueue<int> q;
	int x;
	if (i == 0) 
	{
		m->getwaiting_mission_id(q);

		q.dequeue(x);
		cout << x << " Waiting Missions: ";
	}
	else if (i == 1) 
	{
		 m->getwaiting_rovers_id(q);

		q.dequeue(x);
		cout << x << " Available Rovers: ";
	}
	else if (i == 2) 
	{
		m->get_checkup_rovers(q);

		q.dequeue(x);
		cout << x << " In-Checkup Rovers:  ";
	}
	else if (i == 3)
	{
		m->get_irrcheckup_rovers(q);

		q.dequeue(x);
		cout << x << " Irregular Checkup Rovers:  ";
	}
	q.dequeue(x);
	if (x != 0)
	{
		cout << "[" << x;
		q.dequeue(x);
		while (x != 0) {
			cout << "," << x;
			q.dequeue(x);
		}
		cout << "]  ";

	}


	q.dequeue(x);
	if (x != 0)
	{
		cout << "(" << x;
		q.dequeue(x);
		while (x != 0) {
			cout << "," << x;
			q.dequeue(x);
		}
		cout << ")  ";

	}

	q.dequeue(x);
	if (x != 0)
	{
		cout << "{" << x;
		q.dequeue(x);
		while (x != 0) {
			cout << "," << x;
			q.dequeue(x);
		}
		cout << "} ";

	}
	cout << endl;
}
void ui::print_line2(Marsstation* m)
{
	LinkedQueue<int>qe;
	LinkedQueue<int>qm;
	LinkedQueue<int>qp;
	int x;
	m->getInEcsution_id(qe, qm, qp);
	qe.dequeue(x);
	cout << x << " In-Execution Missions/Rovers: ";

	if (!qe.isEmpty()) 
	{
		qe.dequeue(x);
		cout << "[" << x;
		qe.dequeue(x);
		cout << "/" << x;

		while (!qe.isEmpty()) {
			qe.dequeue(x);
			cout << "," << x;
			qe.dequeue(x);
			cout << "/" << x;
		}
		cout << "]  ";
	}
	if (!qp.isEmpty()) {
		qp.dequeue(x);
		cout << "(" << x;
		qp.dequeue(x);
		cout << "/" << x;

		while (!qp.isEmpty()) {
			qp.dequeue(x);
			cout << "," << x;
			qp.dequeue(x);
			cout << "/" << x;
		}
		cout << ")  ";
	}

	if (!qm.isEmpty()) {
		qm.dequeue(x);
		cout << "{" << x;
		qm.dequeue(x);
		cout << "/" << x;

		while (!qm.isEmpty()) {
			qm.dequeue(x);
			cout << "," << x;
			qm.dequeue(x);
			cout << "/" << x;
		}
		cout << "}  " << endl;
	}
	cout << endl;
}

void ui::print_line5(Marsstation* m,int z) {
	LinkedQueue<int>qe;
	LinkedQueue<int>qm;
	LinkedQueue<int>qp;
	int x;
	if (z == 0) {
		m->getcompleted_missions(qe, qm, qp);
		qe.dequeue(x);
		cout << x << "  Completed Missions:  ";
	}
	else if (z == 1) {
		m->getfailed_missions(qe, qm, qp);
		qe.dequeue(x);
		cout << x << " Failed Mission: ";
	}
	if (!qe.isEmpty())
	{
		qe.dequeue(x);
		cout << "[" << x;


		while (!qe.isEmpty()) {
			qe.dequeue(x);
			cout << "," << x;

		}
		cout << "]  ";
	}
	if (!qp.isEmpty())
	{
		qp.dequeue(x);
		cout << "(" << x;


		while (!qp.isEmpty()) {
			qp.dequeue(x);
			cout << "," << x;

		}
		cout << ")  ";
	}

	if (!qm.isEmpty())
	{
		qm.dequeue(x);
		cout << "{" << x;
		while (!qm.isEmpty()) {
			qm.dequeue(x);
			cout << "," << x;
		}

		cout << "}  " << endl;
	}
	cout << endl;
}

