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
		cout << "SCANNING TARGET SPACE" << endl;
		// Revisit This later for necessity
		if(thisblock->getTopLeftX() < 0 || thisblock->getTopLeftY() < 0 || thisblock->getTopLeftY() > 10 || thisblock->getTopLeftX() > 10)
		{//if the block goes past any edge of the grid
			cout << "PASSED EDGE OF BOARD" << endl;
			return 0;
		}
		// Is the board space that the user is trying to move to open?
		else if(gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] == NULL)
		{
			cout << "SPACE IS OPEN" << endl;
			return 1;
		} 
		else 
		{

		}

		if(gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] != NULL)
		{
			if (!started)
			{
				cout << "COLLISION BEFORE GAME START" << endl;
				return 0;
			}

			// Makes a working copy of the current piece
			Gamepiece* target = gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()];

			// Computer cannot currently play because this checks to ensure it's the user
			// 1 is user, 0 is computer - if it's your piece at that position you cannot move there, else battle
			if(target->getteam() == 1)
			{
				cout << "INVALID PIECE COLLISION" << endl;
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
					cout << "BATTLE ERROR 999" << endl;
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
	cout << "Attempting to take a computer turn..." << endl;
	// METHOD TO DETERMINE WHICH PIECE IS MOVING
	int x = 3;
	int y = 2;
	Gamepiece* compPiece = findcell(x,y);

	// PASS THE MOVING PIECE IN HERE
	if(compPiece == NULL)
	{
		cout << "That space is empty" << endl;
		cout << "try again... Stupid computer" << endl;
	}
	else
	{
		// DETERMINE THE DIRECTION
		move('2',compPiece);
		printGrid();
		cout << "moved computer piece" << endl;
	}

// // C++ program to find the next optimal move for
// // a player

// struct Move
// {
//     int row, col;
// };

// char player = 'x', opponent = 'o';
 
// // This function returns true if there are moves
// // remaining on the board. It returns false if
// // there are no moves left to play.
// bool isMovesLeft(char board[3][3])
// {
//     for (int i = 0; i<3; i++)
//         for (int j = 0; j<3; j++)
//             if (board[i][j]=='_')
//                 return true;
//     return false;
// }
 
// // This is the evaluation function as discussed
// // in the previous article ( http://goo.gl/sJgv68 )
// int evaluate(char b[3][3])
// {
//     // Checking for Rows for X or O victory.
//     for (int row = 0; row<3; row++)
//     {
//         if (b[row][0]==b[row][1] &&
//             b[row][1]==b[row][2])
//         {
//             if (b[row][0]==player)
//                 return +10;
//             else if (b[row][0]==opponent)
//                 return -10;
//         }
//     }
 
//     // Checking for Columns for X or O victory.
//     for (int col = 0; col<3; col++)
//     {
//         if (b[0][col]==b[1][col] &&
//             b[1][col]==b[2][col])
//         {
//             if (b[0][col]==player)
//                 return +10;
 
//             else if (b[0][col]==opponent)
//                 return -10;
//         }
//     }
 
//     // Checking for Diagonals for X or O victory.
//     if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
//     {
//         if (b[0][0]==player)
//             return +10;
//         else if (b[0][0]==opponent)
//             return -10;
//     }
 
//     if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
//     {
//         if (b[0][2]==player)
//             return +10;
//         else if (b[0][2]==opponent)
//             return -10;
//     }
 
//     // Else if none of them have won then return 0
//     return 0;
// }
 
// // This is the minimax function. It considers all
// // the possible ways the game can go and returns
// // the value of the board
// int minimax(char board[3][3], int depth, bool isMax)
// {
//     int score = evaluate(board);
 
//     // If Maximizer has won the game return his/her
//     // evaluated score
//     if (score == 10)
//         return score;
 
//     // If Minimizer has won the game return his/her
//     // evaluated score
//     if (score == -10)
//         return score;
 
//     // If there are no more moves and no winner then
//     // it is a tie
//     if (isMovesLeft(board)==false)
//         return 0;
 
//     // If this maximizer's move
//     if (isMax)
//     {
//         int best = -1000;
 
//         // Traverse all cells
//         for (int i = 0; i<3; i++)
//         {
//             for (int j = 0; j<3; j++)
//             {
//                 // Check if cell is empty
//                 if (board[i][j]=='_')
//                 {
//                     // Make the move
//                     board[i][j] = player;
 
//                     // Call minimax recursively and choose
//                     // the maximum value
//                     best = max( best,
//                         minimax(board, depth+1, !isMax) );
 
//                     // Undo the move
//                     board[i][j] = '_';
//                 }
//             }
//         }
//         return best;
//     }
 
//     // If this minimizer's move
//     else
//     {
//         int best = 1000;
 
//         // Traverse all cells
//         for (int i = 0; i<3; i++)
//         {
//             for (int j = 0; j<3; j++)
//             {
//                 // Check if cell is empty
//                 if (board[i][j]=='_')
//                 {
//                     // Make the move
//                     board[i][j] = opponent;
 
//                     // Call minimax recursively and choose
//                     // the minimum value
//                     best = min(best,
//                            minimax(board, depth+1, !isMax));
 
//                     // Undo the move
//                     board[i][j] = '_';
//                 }
//             }
//         }
//         return best;
//     }
// }
 
// // This will return the best possible move for the player
// Move findBestMove(char board[3][3])
// {
//     int bestVal = -1000;
//     Move bestMove;
//     bestMove.row = -1;
//     bestMove.col = -1;
 
//     // Traverse all cells, evalutae minimax function for
//     // all empty cells. And return the cell with optimal
//     // value.
//     for (int i = 0; i<3; i++)
//     {
//         for (int j = 0; j<3; j++)
//         {
//             // Check if celll is empty
//             if (board[i][j]=='_')
//             {
//                 // Make the move
//                 board[i][j] = player;
 
//                 // compute evaluation function for this
//                 // move.
//                 int moveVal = minimax(board, 0, false);
 
//                 // Undo the move
//                 board[i][j] = '_';
 
//                 // If the value of the current move is
//                 // more than the best value, then update
//                 // best/
//                 if (moveVal > bestVal)
//                 {
//                     bestMove.row = i;
//                     bestMove.col = j;
//                     bestVal = moveVal;
//                 }
//             }
//         }
//     }
 
//     printf("The value of the best Move is : %dnn",
//             bestVal);
 
//     return bestMove;
// }
 
// // Driver code
// int main()
// {
//     char board[3][3] =
//     {
//         { 'x', 'o', 'x' },
//         { 'o', 'o', 'x' },
//         { '_', '_', '_' }
//     };
 
//     Move bestMove = findBestMove(board);
 
//     printf("The Optimal Move is :n");
//     printf("ROW: %d COL: %dnn", bestMove.row,
//                                   bestMove.col );
//     return 0;
// }
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




