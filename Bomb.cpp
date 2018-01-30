//Filename: BOMB.CPP

#include "Bomb.h"

using namespace std;


Bomb::Bomb(int a, int b, int c, int d, int thisID,string btype): Gamepiece(0,b,c,d,thisID,"BOMB")
{
	
}
	
bool Bomb::canmove()
{
	return 0;	
}
	
bool Bomb::canattack()
{
	return 0;
}

string Bomb::getDisplay()
{

	if (team == 2)
	{
		return " # ";
	}
	else
	{
		return " B ";
	}
}

bool Bomb::isfixed()
{
	return 1;	
}

Bomb::~Bomb()
{

}

