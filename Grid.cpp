//Filename: GRID.CPP

#include "Grid.h"


Grid::Grid(int a, int b) {
	numREM = 0;
	numMOV = 0;
	winner = 0;
	gridW = a; 
	gridH = b;
			
	for(int i = 0; i < gridW; i++)
	{
		for(int j = 0; j < gridH; j++)
		{
			theGridd[make_pair(i,j)] = NULL;
		}
	}
}
	



void Grid::printGrid(){
	cout << endl;
	cout << "      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |" << endl;
	cout << endl;
	cout << "---   + - + - + - + - + - + - + - + - + - +   ---" << endl;
		for(int j = 0; j < gridH; j++)
		{
			cout << " " << j << "    " ;
			for(int i = 0; i < gridW; i++)
			{
				
				cout << "|";
				
				if( theGridd[make_pair(i, j)] != NULL )
				{
					cout << theGridd[make_pair(i, j)]->getDisplay();
				}
				else
				{
					cout << "   ";
				}
				
			}
			cout << "|    " << j << endl;
			cout << "---   + - + - + - + - + - + - + - + - + - +   ---" << endl;
			
		}
	cout << endl;
	cout << "      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |" << endl;
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
	numMOV+= num;
}
	
int Grid::gettotal(){ // total number of blocks from creation of the grid
	return blocklist.size();
}
	
	
Gamepiece* Grid::findcell(int x, int y){
	return theGridd[make_pair(x,y)];
}
	
int Grid::seeopen(Gamepiece* thisblock, bool started){
		
		if(thisblock->getTopLeftX() < 0 || thisblock->getTopLeftY() < 0 || ( thisblock->getTopLeftY() + thisblock->getblockH() ) > gridH ||  ( thisblock->getTopLeftX() + thisblock->getblockW() )> gridW)
		{//if the block goes past any edge of the grid
			return 0;
		}
		for(int i = 0; i < thisblock->getblockH(); i++)
		{//the loops should only run once since a gamepice is only one block across
			for(int j = 0; j < thisblock->getblockW(); j++)
			{
				if(theGridd[make_pair(i + thisblock->getTopLeftX(), j + thisblock->getTopLeftY())] != NULL)
				{
					if (!started)
					{
						return 0;
					}
					Gamepiece* target = theGridd[make_pair(i + thisblock->getTopLeftX(), j + thisblock->getTopLeftY())];
					if( target->getteam() == 1)
					{
						return 0;
					}
					else
					{
						char res = battle(thisblock,target);
						switch ( res ) 
						{  
						case '1' :  
							delete thisblock;
							for(int i = 0; i < target->getblockH(); i++)
							{
								for(int j = 0; j < target->getblockW(); j++)
								{
									theGridd[make_pair(i + target->getTopLeftX(), j + target->getTopLeftY())] = NULL;
								}
							}
							delete target;
							return 2;
							break;  
						case '2' :  
							for(int i = 0; i < target->getblockH(); i++)
							{
								for(int j = 0; j < target->getblockW(); j++)
								{
									theGridd[make_pair(i + target->getTopLeftX(), j + target->getTopLeftY())] = NULL;
								}
							}
							delete target;
							return 1;
							break;  
						case '3' :  
							delete thisblock;
							return 2;
							break;  
						case '4' :  
							return 3;
							break;  
						case '5' :  
							for(int i = 0; i < target->getblockH(); i++)
							{
								for(int j = 0; j < target->getblockW(); j++)
								{
									theGridd[make_pair(i + target->getTopLeftX(), j + target->getTopLeftY())] = NULL;
								}
							}
							delete target;
							winner = thisblock->getteam();
							return 1;
							break;  
						default: 
							return 999;		      
						}  
						return 1;
					}
					
				}
				
			}
		}
		
		return 1;
}

bool Grid::addGamepiece(Gamepiece* thisblock) {
		if(seeopen(thisblock, 0))
		{
			for(int i = 0; i < thisblock->getblockH(); i++)
			{
				for(int j = 0; j < thisblock->getblockW(); j++)
				{
					theGridd[make_pair(i + thisblock->getTopLeftX(), j + thisblock->getTopLeftY())] = thisblock;
				}
			}
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
	

		//removes the block before checking for clear spaces
		for(int i = 0; i < thisblock->getblockH(); i++)
			{
				for(int j = 0; j < thisblock->getblockW(); j++)
				{
					theGridd[make_pair(i + thisblock->getTopLeftX(), j + thisblock->getTopLeftY())] = NULL;
				}
			}

			
		
		tempblock->move1(xshift, yshift);
		//checks to see if anything would be in the way
		int cdetect = seeopen(tempblock, 1);
		if( cdetect == 1)
		{
			for(int i = 0; i < thisblock -> getblockH(); i++)
			{
				for(int j = 0; j < thisblock -> getblockW(); j++)
				{
					theGridd[make_pair (i + thisblock->getTopLeftX(), j + thisblock->getTopLeftY() )] = NULL;
				}
			}
			//moves if the space is clear
			thisblock->move1(xshift, yshift);


			
			//put the block in the new place
				for(int i = 0; i < thisblock->getblockH(); i++)
				{
					for(int j = 0; j < thisblock->getblockW(); j++)
					{
						theGridd[make_pair( thisblock->getTopLeftX() + i , thisblock->getTopLeftY() + j )] = thisblock;
					}
				}
				delete tempblock;//the temp block isn't needed anymore
			
			
		}
		else if (cdetect == 0)
		{
			cout << endl;
			cout << "You can't move there!" << endl;
			cout << endl;

			for(int i = 0; i < thisblock->getblockH(); i++)	
			{//put the block back where it belongs
				for(int j = 0; j < thisblock->getblockW(); j++)
				{
					theGridd[make_pair(i + thisblock->getTopLeftX(), j + thisblock->getTopLeftY())] = thisblock;
				}
			}			
			delete tempblock;//the temp block isn't needed anymore
		}
		else if (cdetect == 3)
		{
			for(int i = 0; i < thisblock->getblockH(); i++)	
			{//put the block back where it belongs
				for(int j = 0; j < thisblock->getblockW(); j++)
				{
					theGridd[make_pair(i + thisblock->getTopLeftX(), j + thisblock->getTopLeftY())] = thisblock;
				}
			}			
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

vector<string> Grid::scancount(int tplayer){
	tdisplays.clear();
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(theGridd[make_pair(i, j)] != NULL)
			{
				if((theGridd[make_pair(i, j)])->getteam() == tplayer)
				{
					tdisplays.push_back((theGridd[make_pair(i, j)])->getDisplay());
				}
			}
		}
	}
	return tdisplays;
}




