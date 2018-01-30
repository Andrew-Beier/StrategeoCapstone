//Filename: BOMB.H
#ifndef BOMB_H
#define BOMB_H

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


class Bomb : public Gamepiece {
    public:
	Bomb(int , int , int , int , int ,string);
	virtual string getDisplay();
	virtual ~Bomb();
	virtual bool canattack();
	virtual bool canmove();	
    virtual bool isfixed();
};


#endif