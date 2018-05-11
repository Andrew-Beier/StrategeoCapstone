//Filename: BOMB.CPP

// This is a complete class
#include "Bomb.h"

using namespace std;


Bomb::Bomb(int a, int b, int c, int d, int thisID, string btype): Gamepiece(0,b,c,d,thisID,"BOMB"){

}

bool Bomb::canmove(){
	return false;
}

bool Bomb::canattack(){
	return false;
}

string Bomb::getDisplay(){

	if (team == 2)
	{
		return " # ";
	}
	else
	{
		return " B ";
	}
}

bool Bomb::isfixed(){
	return true;
}

Bomb::~Bomb() = default;