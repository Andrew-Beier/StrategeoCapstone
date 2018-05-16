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
#include <cstdlib>

#include "Gamepiece.h"


class Bomb : public Gamepiece {
public:
    Bomb(int, int, int, int);

    string getDisplay() override;

    ~Bomb() override;

    bool canattack() override;

    bool canmove() override;

    bool isfixed() override;
};


#endif