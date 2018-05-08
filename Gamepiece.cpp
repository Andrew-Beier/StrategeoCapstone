//Filename: Gamepiece.cpp
#include "Gamepiece.h"

// This is complete for now

// Farsides, etc need to be removed / renamed for 1x1 block simplicity
Gamepiece::Gamepiece(int a, int b, int c, int d, int thisID, string btype){
	power= a;
	team = b;
	// c is the x coordinate
	// d is the y coordinate
	topleftX = c;
	topleftY = d;
	id = thisID;
	blocktype = btype;
	farsideX = c;
	farsideY = d;	
}

Gamepiece::Gamepiece(){
	power = 0;
	team = 1;
	topleftX = 0;
	topleftY = 0;
	id = 9999;
	blocktype = "TYPELESS";
	farsideX = 0;
	farsideY = 0;
}

int Gamepiece::getId(){
	return id;
}

string Gamepiece::getType(){
	return blocktype;
}

int Gamepiece::getblockW(){
	return 1;
}

int Gamepiece::getblockH(){
	return 1;
}
	
int Gamepiece::getTopLeftX(){
	return topleftX;
}

int Gamepiece::getTopLeftY(){
	return topleftY;
}

int Gamepiece::getfarsideX(){
	return farsideX;
}
	
int Gamepiece::getfarsideY(){
	return farsideY;
}
	
int Gamepiece::getpower(){
	return power;
}

int Gamepiece::getteam(){
	return team;
}

void Gamepiece::move1(int x, int y) {
	//moves 1 space in any given direction
	topleftX += x;
	farsideX += x;
		
	topleftY += y;
	farsideY += y;
	cout << "move1 fuction activated " << x << " , " << y << endl;
}

bool Gamepiece::canmove(){
	return 1;	
}
	
bool Gamepiece::canattack(){
	return 1;
}

string Gamepiece::getDisplay(){
	if (0)//CHANGE BACK TO (team == 2)
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

Gamepiece::~Gamepiece(){

}

bool Gamepiece::isfixed(){
	return 0;
}

