
//Filename: Flag.cpp

// This is a complete class

#include "Flag.h"

using namespace std;


Flag::Flag(int b, int c, int d, int thisID) : Gamepiece(12, b, c, d, thisID, "FLAG") {

}

bool Flag::canmove() {
    return false;
}

bool Flag::canattack() {
    return false;
}

string Flag::getDisplay() {
    if (team == 2) {
        return " # ";
    } else {
        return " F ";
    }
}

bool Flag::isfixed() {
    return true;
}


Flag::~Flag()
= default;