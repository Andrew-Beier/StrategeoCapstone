//Filename: GRID.CPP

#include "Grid.h"

// TODO Clean up these arguments later
Grid::Grid(int a, int b) {
	numREM = 0;
	numMOV = 0;
	winner = 0;
	gridW = 10; 
	gridH = 10;

	// Create the gameboard - Creates a 2D array (10x10) of gamepiece's in each position
	gameboard = new Gamepiece**[10];

	for(int i = 0; i < 10; i++)
	{
		gameboard[i] = new Gamepiece*[10];
		for(int j = 0; j < gridH; j++)
		{
			gameboard[i][j] = NULL;
		}
	}
}

void Grid::printGrid(){
	cout << endl;
	cout << "      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
	cout << endl;
	cout << "---   + - + - + - + - + - + - + - + - + - + - +   ---" << endl;
		for(int i = 0; i < gridH; i++)
		{
			cout << " " << i << "    " ;
			for(int j = 0; j < gridW; j++)
			{
				
				cout << "|";
				
				if(gameboard[j][i] != NULL )
				{
					// Print the char that indicates the piece
					cout << gameboard[j][i]->getDisplay();
				}
				else
				{
					// If there isn't a piece, print an empty space
					cout << "   ";
				}
				
			}
			cout << "|    " << i << endl;
			cout << "---   + - + - + - + - + - + - + - + - + - + - +   ---" << endl;
			
		}
	cout << endl;
	cout << "      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
}
	
int Grid::getNumREM(){
		return numREM;
}
	
void Grid::changeNumREM(int num){
		numREM+= num;
		numMOV+= num;
}

int Grid::getNumMOV(){ // used to check if anything can be moved
	return numMOV;
}
void Grid::changeNumMOV(int num){
	numMOV += num;
}
	
int Grid::gettotal(){ // total number of blocks from creation of the grid
	return blocklist.size();
}	
	
Gamepiece* Grid::findcell(int x, int y){
	return gameboard[x][y];
}
	
int Grid::seeopen(Gamepiece* thisblock, bool started){
		
		// Revisit This later for necessity
		if(thisblock->getTopLeftX() < 0 || thisblock->getTopLeftY() < 0 || thisblock->getTopLeftY() > 10 || thisblock->getTopLeftX() > 10)
		{//if the block goes past any edge of the grid
			return 0;
		}
		// Is the board space that the user is trying to move to open?
		else if(gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] == NULL)
		{
			return 1;
		} 
		else 
		{

		}

		if(gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] != NULL)
		{
			if (!started)
			{
				return 0;
			}

			// Makes a working copy of the current piece
			Gamepiece* target = gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()];

			// Computer cannot currently play because this checks to ensure it's the user
			// 1 is user, 0 is computer - if it's your piece at that position you cannot move there, else battle
			if(target->getteam() == 1)
			{
				return 0;
			}
			else
			{
				// battle happens
				char res = battle(thisblock,target);
				switch ( res ) 
				{  
				case '1' :  
					// both user and computer pieces are deleted
					delete thisblock;
					gameboard[target->getTopLeftX()][target->getTopLeftY()] = NULL;
					delete target;
					return 2;
					break;  
				case '2' :  
					// Computer won
					gameboard[target->getTopLeftX()][target->getTopLeftY()] = NULL;
					delete target;
					return 1;
					break;  
				case '3' :  
					// User win
					delete thisblock;
					return 2;
					break;  
				case '4' :  
					// unused?
					return 3;
					break;  
				case '5' :
					// flag captured
					gameboard[target->getTopLeftX()][target->getTopLeftY()] = NULL;
					delete target;
					winner = thisblock->getteam();
					return 1;
					break;  
				default: 
					// error
					return 999;		      
				}
				return 1;
			}
		}
return 1;
}

bool Grid::addGamepiece(Gamepiece* thisblock) {
	if(seeopen(thisblock, 0))
	{
		gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = thisblock;
		blocklist.push_back(thisblock);
		return true;
	}
	else
	{
		cout << "You can't put a block there!" << endl;
		cout << endl;
		return false;
	}
}
	
void Grid::move(char direction, Gamepiece* thisblock) {
		int xshift = 0;
		int yshift = 0;
		
		if(thisblock->isfixed())
		{
			cout << "This Piece is IMMOVABLE" << endl;
			cout << "try again..." << endl;
			cout << endl;
			return;
		}
		
		switch ( direction )  //alter shift values to reflect the direction 
		{  
        case '1' :  
			xshift = 0;
			yshift = -1;
			break;  
        case '2' :  
			xshift = 0;
			yshift = 1;
			break;  
		case '3' :  
			xshift = -1;
			yshift = 0;
			break;  
		case '4' :  
			xshift = 1;
			yshift = 0;
			break;  
        default: 
			xshift = 0;
			yshift = 0;		      
		}  
		
		//create a temp block to hold data while moving
		Gamepiece* tempblock = new Gamepiece(thisblock -> getpower(), thisblock -> getteam(), thisblock -> getTopLeftX(), thisblock -> getTopLeftY(), thisblock -> getId(), thisblock -> getType());
	

		// removes the block before checking for clear spaces by setting it's old location to null
		gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = NULL;
			
		
		tempblock->move1(xshift, yshift);
		//checks to see if anything would be in the way
		int cdetect = seeopen(tempblock, 1);
		if( cdetect == 1)
		{
			gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = NULL;

			// Applies movement changes to the correct block if the space is clear
			thisblock->move1(xshift, yshift);


			
			// Write the block in the new place
			gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = thisblock;
			delete tempblock;//the temp block isn't needed anymore
			
			
		}
		else if (cdetect == 0)
		{
			cout << endl;
			cout << "You can't move there!" << endl;
			cout << endl;

			gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = thisblock;		
			delete tempblock;//the temp block isn't needed anymore
		}
		else if (cdetect == 3)
		{
			gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = thisblock;		
			delete tempblock;//the temp block isn't needed anymore
		}
}
	
char Grid::battle(Gamepiece* attacker, Gamepiece* defender){
	cout << endl;
	cout << endl;
	cout<<"Attacker's Power is: " << attacker->getpower() <<endl;
	cout<<"Defender's Power is: " << defender->getpower() <<endl;
	if( defender->getpower() == 12)
	{
		cout<<"A FLAG HAS BEEN CAPTURED!" <<endl;
		return '5';
	}
	
	else if(defender->getpower() == 0)
	{
		if(attacker->getpower() == 8)
		{
			cout<<"The miner defuses a bomb " <<endl;
			cout<<"Defender Removed " <<endl;
			return '2';
		}
		else
		{
			cout<<"The bomb explodes... " <<endl;
			cout<<"Attacker Removed " <<endl;
			return '3';
		}		
	}
	
	else if(defender->getpower() == 1 && attacker->getpower() == 10)
	{
		cout<<"The spy has found its target " <<endl;
		cout<<"Defender Removed " <<endl;
		return '2';
	}
	
	else if(attacker->getpower() < defender->getpower())
	{
		cout<<"Attacker Wins " <<endl;
		cout<<"Defender Removed " <<endl;
		return '2';
	}
	
	else if(attacker->getpower() > defender->getpower())
	{
		cout<<"Defender Wins " <<endl;
		cout<<"Attacker Removed " <<endl;
		return '3';
	}
	
	else if(attacker->getpower() == defender->getpower())
	{
		cout<<"It's a Draw " <<endl;
		cout<<"Both Pieces Removed " <<endl;
		return '1';
	}

	else
	{
		cout<<"Something has gone terribly wrong... " <<endl;
		cout<<"Both Pieces Remain " <<endl;
		return '4';
	}
}

int Grid::findwinner(){
	return winner;
}

void Grid::addComputerPieces(){
	idcounter = 101;
	int blockX;
	int blockY;
	
	for(int i = 0; i < 1; i++)// FLAG
	{
		Gamepiece* p = new Flag(12,2,0,0, idcounter, "FLAG");
		addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 6; i++){ //power 6
		blockX = i;
		Gamepiece* p = new Gamepiece(6,2,i+1,0, idcounter, "SOLDIER");
		addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 2; i++){ // power 2
		blockX = i;
		Gamepiece* p = new Gamepiece(2,2,i+7,0, idcounter, "SOLDIER");
		addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 5; i++){ // BOMBS
		blockX = i;
		Gamepiece* p = new Bomb(0,2,i,1, idcounter, "BOMB");
		addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 4; i++){ // power 4
		blockX = i;
		Gamepiece* p = new Gamepiece(4,2,i+5,1, idcounter, "SOLDIER");
		addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 3; i++){ // power 3
		blockX = i;
		Gamepiece* p = new Gamepiece(3,2,i,2, idcounter, "SOLDIER");
		addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 5; i++){ // power 5
		blockX = i;
		Gamepiece* p = new Gamepiece(5,2,i+3,2, idcounter, "SOLDIER");
		addGamepiece(p);
		idcounter ++;
	}
	
	for(int i = 0; i < 1; i++){ // power 1
		blockX = i;
		Gamepiece* p = new Gamepiece(1,2,8,2, idcounter, "SOLDIER");
		addGamepiece(p);
		idcounter ++;
	}
}

void Grid::takeComputerTurn(){
	cout << "The stupid computer player refuses to move a piece..." << endl;
}

vector<string> Grid::scancount(int tplayer){
	tdisplays.clear();
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(gameboard[i][j] != NULL)
			{
				if((gameboard[i][j])->getteam() == tplayer)
				{
					tdisplays.push_back((gameboard[i][j])->getDisplay());
				}
			}
		}
	}
	return tdisplays;
}




