//Filename: Cplayer.h
#ifndef CPLAYER_H
#define CPLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include <iostream>
#include <string>
#include <cstdlib> 
#include <stdlib.h>
#include "Gamepiece.h"
#include "Grid.h"
#include "Flag.h"
#include "Bomb.h"

using namespace std;

class Cplayer
{
    protected:
		vector<int> piecelist;
		Grid* game;
		int idcounter;
		
	public:
		Cplayer(Grid*);
		int taketurn();

};

#endif