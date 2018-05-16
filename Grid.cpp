//Filename: GRID.CPP

#include "Grid.h"

// TODO Clean up these arguments later
Grid::Grid() {
    numREM = 0;
    numMOV = 0;
    winner = 0;
    gridW = 10;
    gridH = 10;

    // Create the gameboard - Creates a 2D array (10x10) of gamepiece's in each position
    gameboard = new Gamepiece **[10];

    for (int i = 0; i < 10; i++) {
        gameboard[i] = new Gamepiece *[10];
        for (int j = 0; j < gridH; j++) {
            gameboard[i][j] = nullptr;
        }
    }
}

void Grid::printGrid() {
    cout << endl;
    cout << "      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
    cout << endl;
    cout << "---   + - + - + - + - + - + - + - + - + - + - +   ---" << endl;
    for (int i = 0; i < gridH; i++) {
        cout << " " << i << "    ";
        for (int j = 0; j < gridW; j++) {

            cout << "|";

            if (gameboard[j][i] != nullptr) {
                // Print the char that indicates the piece
                cout << gameboard[j][i]->getDisplay();
            } else {
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

int Grid::getNumREM() {
    return numREM;
}

void Grid::changeNumREM(int num) {
    numREM += num;
    numMOV += num;
}

int Grid::getNumMOV() { // used to check if anything can be moved
    return numMOV;
}

void Grid::changeNumMOV(int num) {
    numMOV += num;
}

int Grid::gettotal() { // total number of blocks from creation of the grid
    return static_cast<int>(blocklist.size());
}

Gamepiece *Grid::findcell(int x, int y) {
    return gameboard[x][y];
}

int Grid::seeopen(Gamepiece *thisblock, bool started) {
    // Revisit This later for necessity
    if (thisblock->getTopLeftX() < 0 || thisblock->getTopLeftY() < 0 || thisblock->getTopLeftY() > 10 ||
        thisblock->getTopLeftX() > 10) {//if the block goes past any edge of the grid
        cout << "PASSED EDGE OF BOARD" << endl;
        return 0;
    }
        // Is the board space that the user is trying to move to open?
    else if (gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] == nullptr) {
        return 1;
    } else {

    }

    if (gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] != nullptr) {
        if (!started) {
            cout << "COLLISION BEFORE GAME START" << endl;
            return 0;
        }

        // Makes a working copy of the current piece
        Gamepiece *target = gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()];

        // Computer cannot currently play because this checks to ensure it's the user
        // 1 is user, 0 is computer - if it's your piece at that position you cannot move there, else battle
        if (target->getteam() == thisblock->getteam()) {
            cout << "INVALID PIECE COLLISION" << endl;
            return 0;
        } else {
            // battle happens
            char res = battle(thisblock, target);
            switch (res) {
                case '1' :
                    // both user and computer pieces are deleted
                    delete thisblock;
                    gameboard[target->getTopLeftX()][target->getTopLeftY()] = nullptr;
                    delete target;
                    return 2;
                case '2' :
                    // Computer won
                    gameboard[target->getTopLeftX()][target->getTopLeftY()] = nullptr;
                    delete target;
                    return 1;
                case '3' :
                    // User win
                    delete thisblock;
                    return 2;
                case '4' :
                    return 3;
                case '5' :
                    // flag captured
                    gameboard[target->getTopLeftX()][target->getTopLeftY()] = nullptr;
                    delete target;
                    winner = thisblock->getteam();
                    return 1;
                default:
                    // error
                    cout << "BATTLE ERROR 999" << endl;
                    return 999;
            }
        }
    }
    return 1;
}

bool Grid::addGamepiece(Gamepiece *thisblock) {
    if (seeopen(thisblock, false)) {
        gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = thisblock;
        blocklist.push_back(thisblock);
        return true;
    } else {
        cout << "You can't put a block there!" << endl;
        cout << endl;
        return false;
    }
}

bool Grid::move(char direction, Gamepiece *thisblock) {
    if (thisblock == nullptr) {
        cout << "Attempted to Move NULL PIECE" << endl;
        cout << "try again..." << endl;
        cout << endl;
        return false;
    }
    int xshift = 0;
    int yshift = 0;

    if (thisblock->isfixed()) {
        cout << "This Piece is IMMOVABLE" << endl;
        cout << "try again..." << endl;
        cout << endl;
        return false;
    }

    switch (direction)  //alter shift values to reflect the direction
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
    Gamepiece *tempblock = new Gamepiece(thisblock->getpower(), thisblock->getteam(), thisblock->getTopLeftX(),
                                         thisblock->getTopLeftY(), thisblock->getId(), thisblock->getType());

    // removes the block before checking for clear spaces by setting it's old location to null
    gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = nullptr;

    tempblock->move1(xshift, yshift);
    //checks to see if anything would be in the way
    int cdetect = seeopen(tempblock, true);
    if (cdetect == 1) {
        gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = nullptr;

        // Applies movement changes to the correct block if the space is clear
        thisblock->move1(xshift, yshift);

        // Write the block in the new place
        gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = thisblock;
        delete tempblock;//the temp block isn't needed anymore


    } else if (cdetect == 0) {
        cout << endl;
        cout << "You can't move there!" << endl;
        cout << endl;

        gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = thisblock;
        delete tempblock;//the temp block isn't needed anymore
        return false;
    } else if (cdetect == 3) {
        gameboard[thisblock->getTopLeftX()][thisblock->getTopLeftY()] = thisblock;
        delete tempblock;//the temp block isn't needed anymore
        return true;
    }
    return true;
}

char Grid::battle(Gamepiece *attacker, Gamepiece *defender) {
    cout << endl;
    cout << endl;
    cout << "Attacker's Power is: " << attacker->getpower() << endl;
    cout << "Defender's Power is: " << defender->getpower() << endl;
    if (defender->getpower() == 12) {
        cout << "A FLAG HAS BEEN CAPTURED!" << endl;
        return '5';
    } else if (defender->getpower() == 0) {
        if (attacker->getpower() == 8) {
            cout << "The miner defuses a bomb " << endl;
            cout << "Defender Removed " << endl;
            return '2';
        } else {
            cout << "The bomb explodes... " << endl;
            cout << "Attacker Removed " << endl;
            return '3';
        }
    } else if (defender->getpower() == 1 && attacker->getpower() == 10) {
        cout << "The spy has found its target " << endl;
        cout << "Defender Removed " << endl;
        return '2';
    } else if (attacker->getpower() < defender->getpower()) {
        cout << "Attacker Wins " << endl;
        cout << "Defender Removed " << endl;
        return '2';
    } else if (attacker->getpower() > defender->getpower()) {
        cout << "Defender Wins " << endl;
        cout << "Attacker Removed " << endl;
        return '3';
    } else if (attacker->getpower() == defender->getpower()) {
        cout << "It's a Draw " << endl;
        cout << "Both Pieces Removed " << endl;
        return '1';
    } else {
        cout << "Something has gone terribly wrong... " << endl;
        cout << "Both Pieces Remain " << endl;
        return '4';
    }
}

int Grid::findwinner() {
    return winner;
}

void Grid::addComputerPieces() {
    idcounter = 101;

    for (int i = 0; i < 1; i++)// FLAG
    {
        Gamepiece *p = new Flag(2, 0, 0, idcounter);
        addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 6; i++) { //power 6
        Gamepiece *p = new Gamepiece(6, 2, i + 1, 0, idcounter, "SOLDIER");
        addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 2; i++) { // power 2
        Gamepiece *p = new Gamepiece(2, 2, i + 7, 0, idcounter, "SOLDIER");
        addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 5; i++) { // BOMBS
        Gamepiece *p = new Bomb(2, i, 1, idcounter);
        addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 4; i++) { // power 4
        Gamepiece *p = new Gamepiece(4, 2, i + 5, 1, idcounter, "SOLDIER");
        addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 3; i++) { // power 3
        Gamepiece *p = new Gamepiece(3, 2, i, 2, idcounter, "SOLDIER");
        addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 5; i++) { // power 5
        Gamepiece *p = new Gamepiece(5, 2, i + 3, 2, idcounter, "SOLDIER");
        addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 1; i++) { // power 1
        Gamepiece *p = new Gamepiece(1, 2, 8, 2, idcounter, "SOLDIER");
        addGamepiece(p);
        idcounter++;
    }
	
	for (int i = 0; i < 1; i++) { // The spy
        Gamepiece *p = new Gamepiece(10, 2, 0, 3, idcounter, "SPY");
        addGamepiece(p);
        idcounter++;
    }
	
    for (int i = 1; i < 6; i++) { // Five Miners
        Gamepiece *p = new Gamepiece(8, 2, i, 3, idcounter, "MINER");
        addGamepiece(p);
        idcounter++;
    }

}

// Determine if the piece at a space belongs to the given player
bool Grid::PieceExistsThere(int row, int col, int player) {
    // If there is nothing there, it can't
    if (gameboard[row][col] == nullptr) {
        return false;
    }
    else return gameboard[row][col]->getteam() == player;
}


int Grid::WithinAttackingRange(int row, int col) {

    //1:up, 2:down, 3:left, or 4:right
    if (row - 1 >= 0) {
        if (gameboard[row - 1][col] != nullptr && gameboard[row - 1][col]->getteam() == 2) {
            return 4;
        }
    }
    if (row + 1 <= 9) {
        if (gameboard[row + 1][col] != nullptr && gameboard[row + 1][col]->getteam() == 2) {
            return 3;
        }
    }
    if (col - 1 >= 0) {
        if (gameboard[row][col - 1] != nullptr && gameboard[row][col - 1]->getteam() == 2) {
            return 2;
        }
    }
    if (col + 1 <= 9) {
        if (gameboard[row][col + 1] != nullptr && gameboard[row][col + 1]->getteam() == 2) {
            return 1;
        }
    }
    return 0;
}

void Grid::takeComputerTurn() {
	
	for (int i = 0; i < 1000000000; i++)
	{//Give player a chance to read before computer takes turn
		if(i%200000000==0)
		{
			cout << "....." << endl ;
			//Computer pretends to think
		}
	}
	
    int playerTotal = 0;
    // Absolute Max player Value for the turn prior to any moves
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            // 1 in parameter = is users piece
            if (PieceExistsThere(row, col, 1)) {
                playerTotal += gameboard[row][col]->getpower();
            }
        }
    }

    vector<int> allVals;
    // Assign Values to spaces with a move happening
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            if (PieceExistsThere(row, col, 1)) {
                if (WithinAttackingRange(row, col)) {
                    possMoveWeights[col][row] = playerTotal - gameboard[row][col]->getpower();
                    allVals.push_back(possMoveWeights[col][row]);
                } else {
                    possMoveWeights[col][row] = 888;
                }
                // If the computer has a piece there
            } else if (PieceExistsThere(row, col, 2)) {
                possMoveWeights[col][row] = 999;
                allVals.push_back(possMoveWeights[col][row]);
                // Space is Empty
            } else if (WithinAttackingRange(row, col)) {
                possMoveWeights[col][row] = playerTotal;
                allVals.push_back(possMoveWeights[col][row]);
            } else {
                possMoveWeights[col][row] = 555;
                allVals.push_back(possMoveWeights[col][row]);
            }
        }
    }

    // Copy the values to a new vector
    vector<int> sortedVals;
    for (int allVal : allVals) {
        sortedVals.push_back(allVal);
    }

    sort(sortedVals.begin(), sortedVals.end());
    sortedVals.erase(unique(sortedVals.begin(), sortedVals.end()), sortedVals.end());

    // Find the lowest values on the board with an enemy piece next to it and move that computer piece to the space
    for (int sortedVal : sortedVals) {
        for (int col = 9; col >= 0; col--) {
            for (int row = 9; row >= 0; row--) {
                if (possMoveWeights[col][row] == sortedVal) {
                    int attackOption = WithinAttackingRange(row, col);
                    if (attackOption > 0) {
                        if (attackOption == 1) {
                            Gamepiece *compPiece = findcell(row, col + 1);
                            if (move('1', compPiece)) {
                                return;
                            }
                        } else if (attackOption == 2) {
                            Gamepiece *compPiece = findcell(row, col - 1);
                            if (move('2', compPiece)) {
                                return;
                            }
                        } else if (attackOption == 3) {

                            Gamepiece *compPiece = findcell(row + 1, col);
                            if (move('3', compPiece)) {
                                return;
                            }
                        } else {
                            Gamepiece *compPiece = findcell(row - 1, col);
                            if (move('4', compPiece)) {
                                return;
                            }
                        }
                    } else {
                        continue;
                    }
                } else {
                    continue;
                }
            }
        }
    }
}


vector<string> Grid::scancount(int tplayer) {
    tdisplays.clear();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (gameboard[i][j] != nullptr) {
                if ((gameboard[i][j])->getteam() == tplayer) {
                    tdisplays.push_back((gameboard[i][j])->getDisplay());
                }
            }
        }
    }
    return tdisplays;
}




