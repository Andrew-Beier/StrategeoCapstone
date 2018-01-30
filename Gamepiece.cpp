//Filename: Gamepiece.cpp
#include "Gamepiece.h"


Gamepiece::Gamepiece(int a, int b, int c, int d, int thisID, string btype)
{
	power= a;
	team = b;
	topleftX = c;
	topleftY = d;
	id = thisID;
	blocktype = btype;
	farsideX = c;
	farsideY = d ;	
}
	
int Gamepiece::getId()
{
	return id;
}

string Gamepiece::getType()
{
	return blocktype;
}

int Gamepiece::getblockW()
{
	return 1;
}
int Gamepiece::getblockH()
{
	return 1;
}
	
int Gamepiece::getTopLeftX()
{
	return topleftX;
}
int Gamepiece::getTopLeftY()
{
	return topleftY;
}

int Gamepiece::getfarsideX()
{
	return farsideX;
}
	
int Gamepiece::getfarsideY()
{
	return farsideY;
}
	
int Gamepiece::getpower()
{
	return power;
}

int Gamepiece::getteam()
{
	return team;
}

void Gamepiece::move1(int x, int y)
{//moves 1 space in any given direction
	topleftX += x;
	farsideX += x;
		
	topleftY += y;
	farsideY += y;
}

bool Gamepiece::canmove()
{
	return 1;	
}
	
bool Gamepiece::canattack()
{
	return 1;
}

string Gamepiece::getDisplay()
{
	if (team == 2)
	{
		return " # ";
	}
	else
	{

		stringstream ss;
		ss << " " << power << " ";
		return ss.str();
	}
	
}

Gamepiece::~Gamepiece()
{

}

bool Gamepiece::isfixed()
{
	return 0;
}

