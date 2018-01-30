
/* Andrew Beier HW #7
	I used a vector to hold the display information of all the players pieces.
	I used a map to make the gameboard
	I used .clear, .pushback, and .size when dealing with the vector of display information.
	I could not find a use or need for a lambda or function object for my game, and I will take a small reduction for it.
	I still use inheritance even though it is no longer required
	I used dynamic memory allocation with my classes
	I also use poymorphisim with some of the functions in my classes
	From myers book, I used Items; 4, 7, 9, 13, 21, 22, 32, 36, 37,
	


*/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <list>
#include "Gamepiece.h"
#include "Grid.h"
#include "Flag.h"
#include "Bomb.h"
#include "Cplayer.h"

using namespace std;

// Declare Main Function
int main()
{

	int idcounter = 151;
	string  quitchoice,pname;
	char blockType, direction;
	int gridX = 9;
	int gridY = 9;
	int numblocks = 54;
	int blockDimX = 1;
	int blockDimY = 1; 
	int blockX, blockY;
	int t1pieces = 2;

	int moveX, moveY;

	bool moreMove = true;

	// Create an instance of Gamepiece, b
	Gamepiece* b;	

	// Get and store Player's name
	cout << "Please enter your name: " <<endl;
	cin >> pname;

	// Welcome the player to the game
	cout << "WELCOME TO STRATEGEO TRAINING" << endl;
	cout << endl;
	
	// Create a new instance of a game Grid, given parameters gridY, gridX (size of grid)
	Grid* game = new Grid(gridY,gridX);
	Cplayer* dumbplayer = new Cplayer(game);
	
	// Feedback for UX
	cout << "Printing the Game Board" << endl;
	cout << endl;
	cout << endl;
	
	// Call printGrid method on the game object
	game->printGrid();

	// Add spacing for UX
	cout << endl;
	cout << endl;
	



	
	// MAKE FIVE BOMBS
	cout << "First you need to place 5 bombs" << endl;
	for(int i = 0; i < 5; i++) {
		// Keep track of which bomb is being placed
		cout << "Pick a location for bomb number: " << (i+1) << endl;

		// Get Y Coordinate
		cout << "Pick a X coordinate (left side is 0)" << endl;
		cin >> blockY;
		// Get X Coordinate
		cout << "Pick a Y coordinate (6 to 8)" << endl;
		cin >> blockX;// blockx and Y got switched somehow ???

		// If block is placed within first 3 rows and on the board
		if(blockX >= 6 && blockY <= 8){
			// Create a bomb object to be placed
			Gamepiece* p = new Bomb(0,1,blockY,blockX, idcounter, "BOMB");
			
			if(game->addGamepiece(p)){
				idcounter++;
				cout << "Your Flag has been placed" << endl;
			}
			else
			{
				i--;
				cout << "try again..." << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
			i--;
		}
		game->printGrid();
	}
	
	//MAKE A FLAG
	cout << "Next Place your flag" << endl;
	for(int i = 0; i < 1; i++)//It's a loop in case of a double flag game
	{
		cout << "Pick a location for your flag" <<  endl;

		
		cout << "Pick a X coordinate (left side is 0)" << endl;
		cin >> blockY;
		
		cout << "Pick a Y coordinate (6 to 8)" << endl;
		cin >> blockX;//blockx and Y got switched somehow


		if(blockX >= 6 && blockY <= 8)
		{
			Gamepiece* p = new Flag(9,1,blockY,blockX, idcounter, "FLAG");
			
			if(game->addGamepiece(p))
			{
				idcounter++;
				cout << "Your Flag has been placed" << endl;
			}
			else
			{
				i--;
				cout << "try again..." << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
			i--;
		}
		game->printGrid();
	}
	
	//SIX SIXES
	cout << "Six Soldiers will have power of 6" << endl;
	for(int i = 0; i < 6; i++)
	{
		cout << "Pick a location for 6* soldier number: " << (i+1) << endl;

		
		cout << "Pick a X coordinate (left side is 0)" << endl;
		cin >> blockY;
		
		cout << "Pick a Y coordinate (6 to 8)" << endl;
		cin >> blockX;//block x and Y got switched somehow


		if(blockX >= 6 && blockY <= 8)
		{
			Gamepiece* p = new Gamepiece(6,1,blockY,blockX, idcounter, "SOLDIER");
			
			if(game->addGamepiece(p))
			{
				idcounter++;
				cout << "Your soldier has been placed" << endl;
			}
			else
			{
				i--;
				cout << "try again..." << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
			i--;
		}
		game->printGrid();
	}
	//FIVE FIVES
	cout << "Five Soldiers will have power of 5" << endl;
	for(int i = 0; i < 5; i++)
	{
		cout << "Pick a location for 5* soldier number: " << (i+1) << endl;

		
		cout << "Pick a X coordinate (left side is 0)" << endl;
		cin >> blockY;
		
		cout << "Pick a Y coordinate (6 to 8)" << endl;
		cin >> blockX;//block x and Y got switched somehow


		if(blockX >= 6 && blockY <= 8)
		{
			Gamepiece* p = new Gamepiece(5,1,blockY,blockX, idcounter, "SOLDIER");
			
			if(game->addGamepiece(p))
			{
				idcounter++;
				cout << "Your soldier has been placed" << endl;
			}
			else
			{
				i--;
				cout << "try again..." << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
			i--;
		}
		game->printGrid();
	}
	
	
	//FOUR FOURS
	cout << "four Soldiers will have power of 4" << endl;
	for(int i = 0; i < 4; i++)
	{
		cout << "Pick a location for 4* soldier number: " << (i+1) << endl;

		
		cout << "Pick a X coordinate (left side is 0)" << endl;
		cin >> blockY;
		
		cout << "Pick a Y coordinate (6 to 8)" << endl;
		cin >> blockX;//block x and Y got switched somehow


		if(blockX >= 6 && blockY <= 8)
		{
			Gamepiece* p = new Gamepiece(4,1,blockY,blockX, idcounter, "SOLDIER");
			
			if(game->addGamepiece(p))
			{
				idcounter++;
				cout << "Your soldier has been placed" << endl;
			}
			else
			{
				i--;
				cout << "try again..." << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
			i--;
		}
		game->printGrid();
	}
	
	//THREE THREES
	cout << "four Soldiers will have power of 3" << endl;
	for(int i = 0; i < 3; i++)
	{
		cout << "Pick a location for 3* soldier number: " << (i+1) << endl;

		
		cout << "Pick a X coordinate (left side is 0)" << endl;
		cin >> blockY;
		
		cout << "Pick a Y coordinate (6 to 8)" << endl;
		cin >> blockX;//block x and Y got switched somehow


		if(blockX >= 6 && blockY <= 8)
		{
			Gamepiece* p = new Gamepiece(3,1,blockY,blockX, idcounter, "SOLDIER");
			
			if(game->addGamepiece(p))
			{
				idcounter++;
				cout << "Your soldier has been placed" << endl;
			}
			else
			{
				i--;
				cout << "try again..." << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
			i--;
		}
		game->printGrid();
	}
	
	//TWO TWOS
	cout << "Two Soldiers will have power of 2" << endl;
	for(int i = 0; i < 2; i++)
	{
		cout << "Pick a location for 2* soldier number: " << (i+1) << endl;

		
		cout << "Pick a X coordinate (left side is 0)" << endl;
		cin >> blockY;
		
		cout << "Pick a Y coordinate (6 to 8)" << endl;
		cin >> blockX;//block x and Y got switched somehow


		if(blockX >= 6 && blockY <= 8)
		{
			Gamepiece* p = new Gamepiece(2,1,blockY,blockX, idcounter, "SOLDIER");
			
			if(game->addGamepiece(p))
			{
				idcounter++;
				cout << "Your soldier has been placed" << endl;
			}
			else
			{
				i--;
				cout << "try again..." << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
			i--;
		}
		game->printGrid();
	}
	
	//A SINGLE ONE
	cout << "You only get one soldier with power of 1" << endl;
	for(int i = 0; i < 1; i++)
	{
		cout << "Pick a location for 1* soldier number: " << (i+1) << endl;

		
		cout << "Pick a X coordinate (left side is 0)" << endl;
		cin >> blockY;
		
		cout << "Pick a Y coordinate (6 to 8)" << endl;
		cin >> blockX;//block x and Y got switched somehow


		if(blockX >= 6 && blockY <= 8)
		{
			Gamepiece* p = new Gamepiece(1,1,blockY,blockX, idcounter, "SOLDIER");
			
			if(game->addGamepiece(p))
			{
				idcounter++;
				cout << "Your soldier has been placed" << endl;
			}
			else
			{
				i--;
				cout << "try again..." << endl;
				cout << endl;
			}
		}
		else
		{
			cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
			i--;
		}
		game->printGrid();
	}
	
	cout << endl;
	cout << "THE BOARD IS SET" << endl;
	cout << "This is a training game, so the computer won't attack you" << endl;
	cout << "THE GAME WILL NOW BEGIN!" << endl;
	cout << endl;
	game->printGrid();
	cout << endl;
	cout << endl;
	

	while(moreMove)	//currently endless
	{
			vector<string> pvec = game->scancount(1);//could be used for more, but the other features are not helpfull
			cout << pname << " it is your turn." << endl;
			cout << "You have " << pvec.size() << " pieces under your command" << endl;
			
			
			cout << "Pick a X coordinate for a movable block:" << endl;
			cin >> moveY;
	
			cout <<"Pick an Y Coordinate for a movable block:" << endl;
			cin >> moveX;
			
			if(game->findcell(moveY,moveX) == NULL)
			{
				cout << "That space is empty" << endl;
				cout << "try again..." << endl;
				moreMove = true;
			}
			else if((game->findcell(moveY,moveX))-> getteam() == 2)
			{
				cout << "That is not your piece" << endl;
				cout << "try again..." << endl;
			}
			else
			{
				cout << "Pick a direction 1:up, 2:down, 3:left, or 4:right?" << endl;
				cin >> direction;
			
				b = game->findcell(moveY,moveX);
				game->move(direction,b);

				game->printGrid();
				cout << endl;
			}	
		if (game->findwinner() != 0)
		{
			cout << "PLYAER " <<  game->findwinner() << " WINS!" << endl;
			moreMove = false;
		}
			
	}
	return 0;
}