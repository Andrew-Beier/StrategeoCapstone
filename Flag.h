//Filename: Flag.h
#ifndef FLAG_H
#define FLAG_H

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


class Flag : public Gamepiece
{
    public:
	Flag(int , int , int , int , int ,string);
	virtual string getDisplay();
	virtual ~Flag();
	virtual bool canattack();
	virtual bool canmove();	
	virtual bool isfixed();
    
};

#endif