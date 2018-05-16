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
#include <cstdlib>

#include "Gamepiece.h"


class Flag : public Gamepiece {
public:
    Flag(int, int, int, int);

    string getDisplay() override;

    ~Flag() override;

    bool canattack() override;

    bool canmove() override;

    bool isfixed() override;

};

#endif