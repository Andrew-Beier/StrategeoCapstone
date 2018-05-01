//Filename: Grid.h
#ifndef GRID_H
#define GRID_H

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
#include "Flag.h"
#include "Bomb.h"



using namespace std;

class Grid
{
   private:
		Gamepiece*** gameboard;
		vector<Gamepiece*> blocklist;
		vector<string> tdisplays;
		int gridW;
		int gridH;
		int numMOV;// blocks that can be moved
		int numREM;// blocks that have to be removed
		int winner;
		int idcounter;
		int possMoveWeights[10][10];
		
	public:
		Grid(int, int);
		void printGrid();
		int getNumREM();
		void changeNumREM(int);
		int getNumMOV();
		void changeNumMOV(int);
		int gettotal();
		Gamepiece* findcell(int x, int y);
		int seeopen(Gamepiece*, bool);
		bool addGamepiece(Gamepiece* );
		void move(char, Gamepiece*);
		char battle(Gamepiece*,Gamepiece*);
		int findwinner();
		void takeComputerTurn();
		void addComputerPieces();
		vector<string> scancount(int);
		bool PieceExistsThere(int row, int col, int player);
		int WithinAttackingRange(int row,int col);
};


#endif