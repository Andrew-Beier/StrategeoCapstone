//Filename: Grid.h
#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include <iostream>
#include <string>
#include <cstdlib> 
#include <stdlib.h>

using namespace std;

class Gamepiece
{
    protected:
		string blocktype;
		int power;
		int team;
		int topleftX, topleftY;
		int farsideX, farsideY;
		int id;
		
	public:
		Gamepiece(int , int , int , int , int ,string);
		Gamepiece();
		int getId();
		string getType();
		int getblockW();
		int getblockH();
		int getTopLeftX();
		int getTopLeftY();
		int getfarsideX();
		int getfarsideY();
		int getpower();
		int getteam();
		void move1(int, int);
		virtual string getDisplay();
		virtual ~Gamepiece();
		virtual bool canattack();
		virtual bool canmove();
		virtual bool isfixed();

};

#endif