#include "Rovers.h"
Rovers::Rovers() :Nunber_missions(0), Need_maintanance(false),failed(false)
{
}
Rovers::Rovers(float S, int CH, int i):Nunber_missions(0), Need_maintanance(false), failed(false)
{
	Speed_Of_Rovers = S;
	No_dayes_of_CheckUp = CH;
	Index_Of_Rovers = i;
}

