#pragma once
class Marsstation;
class Event
{

protected:
	int ED;
	int ID;
	Marsstation* m_station;
public:
	Event();
	Event(Marsstation* M_S, int ed, int id);
	virtual void Execute() = 0;
	void set_ED(int ED);
	void set_ID(int id);

	int getED() const;
	int getid() const;

	virtual ~Event() {}
};

