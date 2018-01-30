//Filename: Cplayer.cpp
#include "Cplayer.h"


Cplayer::Cplayer(Grid* game)
{
	idcounter = 101;
	int blockX;
	int blockY;
	
	for(int i = 0; i < 1; i++)// FLAG
	{
		Gamepiece* p = new Flag(9,2,0,0, idcounter, "FLAG");
		game->addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 6; i++)//power 6
	{
		blockX = i;
		Gamepiece* p = new Gamepiece(6,2,i+1,0, idcounter, "SOLDIER");
		game->addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 2; i++)// power 2
	{
		blockX = i;
		Gamepiece* p = new Gamepiece(2,2,i+7,0, idcounter, "SOLDIER");
		game->addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 5; i++)// BOMBS
	{
		blockX = i;
		Gamepiece* p = new Bomb(0,2,i,1, idcounter, "BOMB");
		game->addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 4; i++)// power 4
	{
		blockX = i;
		Gamepiece* p = new Gamepiece(4,2,i+5,1, idcounter, "SOLDIER");
		game->addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 3; i++)// power 3
	{
		blockX = i;
		Gamepiece* p = new Gamepiece(3,2,i,2, idcounter, "SOLDIER");
		game->addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 5; i++)// power 5
	{
		blockX = i;
		Gamepiece* p = new Gamepiece(5,2,i+3,2, idcounter, "SOLDIER");
		game->addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 1; i++)// power 1
	{
		blockX = i;
		Gamepiece* p = new Gamepiece(1,2,8,2, idcounter, "SOLDIER");
		game->addGamepiece(p);
		idcounter ++;
	}

}

int Cplayer::taketurn()
{
	cout << "The stupid computer player refuses to move a piece..." << endl;
		//I was going to make move random pieces in random directions, but that is too much work for this project
}
	
	
	
	
	