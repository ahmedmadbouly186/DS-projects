#pragma once
#include<iostream>
#include<string>
using namespace std;
class Marsstation;
class ui
{
	string filename;
public:
	string getfilename();
	void invalid() {
		printmsg("invalid name ");
		cout <<  endl;
	}
	void printmsg(string x) {
		cout << x<<endl;
	}
	int getint() {
		int x;
		cin >> x;
		return x;
	}

	void silentmode();
	void stepbystepmode(Marsstation* m);
	void interactivemode(Marsstation* m);
	void print_line1(Marsstation* m,int i);
	void print_line2(Marsstation* m);
	void print_line5(Marsstation* m,int z);
	void print(Marsstation* m);
};

