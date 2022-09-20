#include "Marsstation.h"
int main()
{
	Marsstation M_S;
	bool failed;
	failed = M_S.read_data();
	if (failed)
	{
		M_S.Set_Mode();
		while (!M_S.IsEnd())
		{
			M_S.Start();
		}
	}
	return 0;
}