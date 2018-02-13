//Filename: Flag.cpp

#include "Flag.h"

using namespace std;


Flag::Flag(int a, int b, int c, int d, int thisID,string btype): Gamepiece(12,b,c,d,thisID,"FLAG")
{
	
}

bool Flag::canmove()
{
	return 0;	
}
	
bool Flag::canattack()
{
	return 0;
}

string Flag::getDisplay()
{
	if (team == 2)
	{
		return " # ";
	}
	else
	{
		return " F ";
	}
}

bool Flag::isfixed()
{
	return 1;
}


Flag::~Flag()
{

}