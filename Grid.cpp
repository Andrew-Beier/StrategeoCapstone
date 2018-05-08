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
	
bool Grid::move(char direction, Gamepiece* thisblock) {
	cerr << "Made it to the move function; values are... Direction: " + to_string(direction) + " block type: " << endl;
	cerr << thisblock->getType() << endl;
		int xshift = 0;
		int yshift = 0;
		
		if(thisblock->isfixed())
		{
			cout << "This Piece is IMMOVABLE" << endl;
			cout << "try again..." << endl;
			cout << endl;
			return false;
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
			return false;
		}
		else if (cdetect == 3)
		{
			gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = thisblock;		
			delete tempblock;//the temp block isn't needed anymore
			return true;
		}
	return true;
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

// Determine if the piece at a space belongs to the given player
bool Grid::PieceExistsThere(int row, int col, int player){
	//cerr << "Near line 385 inside the PieceExistsThere Function, values are; Row:  " + to_string(row) + " Col: " + to_string(col) + " Player: " + to_string(player) << endl;
	// If there is nothing there, it can't
	if(gameboard[row][col] == NULL){
		return false;
	}
	//
	else if(gameboard[row][col]->getteam() == player){
		return true;
	}
	else{
		return false;
	}
}


int Grid::WithinAttackingRange(int row,int col) {
	cerr << "Near line 401: inside the WithinAttackingRange Function, values are; Row:  " + to_string(row) + " Col: " + to_string(col) << endl;

	//1:up, 2:down, 3:left, or 4:right
	if(!(row-1 < 0)){
		//cerr << "Near line 405: row-1 is not less than 0, continuing to check if it's a user piece" << endl;
		if(gameboard[row-1][col] != NULL && gameboard[row-1][col]->getteam() == 2){
			//cerr << "Line 405: Made it within return 3 option" << endl;
			return 2;
		}
	}
	if(!(row+1 > 9)) {
		//cerr << "Near line 414: row+1 is not higher than 9, continuing to check if it's a user piece" << endl;
		if(gameboard[row+1][col] != NULL && gameboard[row+1][col]->getteam() == 2){
			//cerr << "Line 412: Made it within return 4 option" << endl;
			return 1;
		}
	}
	if(!(col - 1 < 0)) {
		//cerr << "Near line 405: col-1 is not less than 0, continuing to check if it's a user piece" << endl;

		if(gameboard[row][col-1] != NULL && gameboard[row][col-1]->getteam() == 2){

			//cerr << "Line 417: Made it within return 1 option" << endl;
			return 4;
		}
	}
	if(!(col+1 > 9)){
		//cerr << "Near line 405: col+1 is not higher than 9, continuing to check if it's a user piece" << endl;
		if(gameboard[row][col+1] != NULL && gameboard[row][col+1]->getteam() == 2){
			//cerr << "Line 422: Made it within return 2 option" << endl;
			return 3;
		}
	}

	cerr << "Line 420: Made it within return 0 option" << endl;
	return 0;
}

void Grid::takeComputerTurn(){
	cerr << " Near line 418: Attempting to take a computer turn..." << endl;

	int playerTotal = 0;
	// Absolute Max player Value for the turn prior to any moves
	cerr << "Near line 422: Calculating total value of playerTotal" << endl;
	for(int row = 0; row < 10; row++){
		for(int col = 0; col < 10; col++){
			// 1 in paramter = is users piece
			if(PieceExistsThere(row,col,1)){
				playerTotal += gameboard[row][col]->getpower();
			}
		}
	}
	cerr << "Near line 430: Determined the max value, it is: " + to_string(playerTotal) << endl;
	vector<int> allVals;
	// Assign Values to spaces with a move happening
	for(int row = 0; row < 10; row++) {
		for (int col = 0; col < 10; col++) {
			if (PieceExistsThere(row, col, 1)) {
				if(WithinAttackingRange(row, col)){
					cerr << "Near Line 437: Determiend that a user piece is there" << endl;
					possMoveWeights[col][row] = playerTotal - gameboard[row][col]->getpower();
					cerr << "Near Line 439: Value adding to the allVals vector is: " + to_string(possMoveWeights[row][col]) << endl;
					allVals.push_back(possMoveWeights[col][row]);
				}
				else{
					possMoveWeights[col][row] = 1000;
				}
				// If the computer has a piece there
			} else if (PieceExistsThere(row, col, 2)) {
				cerr << "Near Line 443: Determiend that a computer piece is there" << endl;

				possMoveWeights[col][row] = 1000;
				allVals.push_back(possMoveWeights[col][row]);
				cerr << "Near Line 445: Value adding to the allVals vector is: 1000 " << endl;
				// Space is Empty
			} else {
				cerr << "Near Line 450: Determined that there is not a  piece there" << endl;
				possMoveWeights[col][row] = playerTotal;
				cerr << "Near line 452: Weight being added is: " + to_string(possMoveWeights[row][col]) << endl;
				allVals.push_back(possMoveWeights[col][row]);
			}
		}
	}
	// Print the grid
	cerr << "Near Line 458: Printing Grid" << endl;
	cout << endl;
	cout << "      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
	cout << endl;
	cout << "---   + - + - + - + - + - + - + - + - + - + - +   ---" << endl;
	for(int row = 0; row < 10; row++){
		cout << " " << row << "    " ;
		for(int col = 0; col <10; col++){
			cout << "|";

			// Print the char that indicates the piece
			cout << possMoveWeights[row][col];

		}
				cout << "|    " << row << endl;
				cout << "---   + - + - + - + - + - + - + - + - + - + - +   ---" << endl;

	}
	cout << endl;
	cout << "      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;

	//cerr << " Near Line 449: Made it past the loop that assigns values to the allVals Vector" << endl;
	// Copy the values to a new vector
	vector<int> sortedVals;
	for(int i = 0; i < allVals.size(); i++) {
		sortedVals.push_back(allVals[i]);
	}
	/*
	cerr << " printing alvals vector" << endl;
	for(int i = 0; i < sortedVals.size(); i++) {
		cout << (sortedVals[i]) << endl;
	}
	*/
	
	//cerr << " Near line 455: Made it past the loop that copies values from the allVals Vector to the sortedVals" << endl;
	

	sort(sortedVals.begin(),sortedVals.end());
	sortedVals.erase( unique( sortedVals.begin(), sortedVals.end() ), sortedVals.end() );
	cerr << " printing sorted vector" << endl;
	for(int i = 0; i < sortedVals.size(); i++) {
		cout << (sortedVals[i]) << endl;
	}

	cerr << "Near line 458: Made it past the function that sorts values in the sortedVals Vector" << endl;

	// Find the lowest values on the board with an enemy piece next to it and move that computer piece to the space
	for(int lowestPossValueIndex = 0; lowestPossValueIndex < sortedVals.size(); lowestPossValueIndex++) {
		cerr << "Near Line 462: Inside the lowestPossValueIndex for loop" << endl;
		cerr << "Near line 463: Current value for lowestPossValueIndex is: " + to_string(lowestPossValueIndex) << endl;

		for (int col = 0; col < 10; col++) {
			for (int row = 0; row < 10; row++) {
				if (possMoveWeights[row][col] == sortedVals[lowestPossValueIndex]) {
					cerr << "Near line 468: The value at the possMoveWeights[row][col] is equal to the lowest value in sortedVals: " + to_string(sortedVals[lowestPossValueIndex]) << endl;
					int attackOption = WithinAttackingRange(row,col);
					cerr << "near line 470: attackOption was just returned, it is: " + to_string(attackOption) << endl;
					if (attackOption > 0) {
						cerr << "near line 472: attackOption is greater than 0" << endl;

						if(attackOption == 1) {
							cerr << "near line 475: attackOption is 1" << endl;
							Gamepiece* compPiece = findcell(row+1,col);
							cerr << "near line 477: assigned a Gampiece pointer named compPiece" << endl;
							cerr << "near line 478: Attempting to move piece upwards..." << endl;
							if(move('1',compPiece)){
								return;
							}
							cerr << " near line 480: piece was moved upwards" << endl;
						} else if (attackOption == 2) {
							cerr << "near line 482: attackOption is 2" << endl;

							Gamepiece* compPiece = findcell(row-1,col);
							cerr << "near line 485: assigned a Gampiece pointer named compPiece" << endl;
							cerr << "near line 486: Attempting to move piece down..." << endl;
							if(move('2',compPiece)){
								return;
							}
							cerr << "near line 488: piece was moved down" << endl;
						} else if(attackOption == 4) {
							cerr << "near line 490: attackOption is 3" << endl;

							Gamepiece* compPiece = findcell(row,col-1);
							cerr << "near line 493: assigned a Gampiece pointer named compPiece" << endl;
							cerr << "near line 494: Attempting to move piece left..." << endl;
							if(move('3',compPiece)){
								return;
							}
							cerr << "near line 496: piece was moved left" << endl;
						} else {
							cerr << "near line 498: attackOption should be 4, it is: " + to_string(attackOption) << endl;
							Gamepiece* compPiece = findcell(row,col+1);
							cerr << "near line 500: assigned a Gampiece pointer named compPiece" << endl;
							cerr << "near line 501: Attempting to move piece right..." << endl;
							if(move('4',compPiece)){
								return;
							}
							cerr << "near line 503: piece was moved right" << endl;
						}
					} else {
						cerr << "near line 506: There were no possible moves towards this space" << endl;
						continue;
					}
				} else {
					cerr << "near line 510: This spot is not the current lowest value being looked at" << endl;
					continue;
				}
			}
		}
	}


//			if(pieceExistsThere(row,col,2)){
//				// dir 1 is up; 2 is down; 3 is left; 4 is right
//				for(int dir = 1; dir < 5; dir++){
//					if(dir == 1){
//						// direction is up
//						if(!(row - 1 < 0)){
//							possMoveWeights[row][col][dir] = 10000;
//						}
//						else if (pieceExistsThere(row-1,col,1)){
//							possMoveWeights[row][col][dir] = playerTotal - (gameboard[row-1][col].getpower());
//						}
//					} else if (dir == 2){
//						// direction is down
//						if(!(row + 1 > 10)){
//							possMoveWeights[row][col][dir] = 10000;
//						}
//						else if(pieceExistsThere(row+1,col,1)){
//							possMoveWeights[row][col][dir] = playerTotal - (gameboard[row-1][col].getpower());
//						}
//					} else if (dir == 3){
//						// direction is left
//						if(!(col - 1 < 0)){
//							possMoveWeights[row][col][dir] = 10000;
//						}
//						else if(pieceExistsThere(row,col-1,1)){
//							possMoveWeights[row][col][dir] = playerTotal - (gameboard[row-1][col].getpower());
//						}
//					} else {
//						// dir == 4 direction is right
//						if(!(col + 1 > 10)){
//							possMoveWeights[row][col][dir] = 10000;
//						}
//						else if(pieceExistsThere(row,col+1,1)){
//							possMoveWeights[row][col][dir] = playerTotal - (gameboard[row-1][col].getpower());
//						}
//					}
//				}
//			}
//			else {
//				// There isn't a piece there so every weight is high
//				for(int dir = 0; dir < 4; dir++){
//					possMoveWeights[row][col][dir] = 10000;
//				}
//			}
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




