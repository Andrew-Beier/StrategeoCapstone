
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <list>
// Compiled Classes
#include "Gamepiece.h"
#include "Grid.h"
#include "Flag.h"
#include "Bomb.h"

using namespace std;

// For development - Currently setup to auto create the grid in a typical order

// Add Remaining pieces movement

// Declare Main Function
int main() {

    // Starting ID # for pieces
    int idcounter = 151;
    string quitchoice, pname;
    char direction;
    // coordinate for position
    int blockX, blockY;
    // Movement magnitude
    int moveX, moveY;
    // Check to see if game should continue (actual game loop)
    bool moreMove = true;
    bool customSetup = false;

    // Create an instance of Gamepiece, b
    Gamepiece *b;

    // Get and store Player's name
    cout << "Please enter your name: " << endl;
    cin >> pname;

    // Welcome the player to the game
    cout << "WELCOME TO STRATEGEO TRAINING" << endl;
    cout << endl;

    // Create a new instance of a game Grid
    auto *game = new Grid();
    game->addComputerPieces();

    // Feedback for UX
    cout << "Printing the Game Board" << endl;
    cout << endl;
    cout << endl;

    // Call printGrid method on the game object
    game->printGrid();

    // Add spacing for UX
    cout << endl;
    cout << endl;

    //Custom Setup is Disabled for Testing Purposes
    if (customSetup) {
        // MAKE FIVE BOMBS
        cout << "First you need to place 5 bombs" << endl;
        for (int i = 0; i < 5; i++) {
            // Keep track of which bomb is being placed
            cout << "Pick a location for bomb number: " << (i + 1) << endl;

            // Get Y Coordinate
            cout << "Pick a X coordinate (left side is 0)" << endl;
            cin >> blockY;
            // Get X Coordinate
            cout << "Pick a Y coordinate (6 to 8)" << endl;
            cin >> blockX;// blockx and Y got switched somehow ???

            // If block is placed within first 3 rows and on the board
            if (blockX >= 6 && blockY <= 8) {
                // Create a bomb object to be placed
                Gamepiece *p = new Bomb(1, blockY, blockX, idcounter);

                if (game->addGamepiece(p)) {
                    idcounter++;
                    cout << "Your Flag has been placed" << endl;
                } else {
                    i--;
                    cout << "try again..." << endl;
                    cout << endl;
                }
            } else {
                cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
                i--;
            }
            game->printGrid();
        }

        //MAKE A FLAG
        cout << "Next Place your flag" << endl;
        for (int i = 0; i < 1; i++) {
            cout << "Pick a location for your flag" << endl;


            cout << "Pick a X coordinate (left side is 0)" << endl;
            cin >> blockY;

            cout << "Pick a Y coordinate (6 to 8)" << endl;
            cin >> blockX;//blockx and Y got switched somehow


            if (blockX >= 6 && blockY <= 8) {
                Gamepiece *p = new Flag(1, blockY, blockX, idcounter);

                if (game->addGamepiece(p)) {
                    idcounter++;
                    cout << "Your Flag has been placed" << endl;
                } else {
                    i--;
                    cout << "try again..." << endl;
                    cout << endl;
                }
            } else {
                cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
                i--;
            }
            game->printGrid();
        }

        //SIX SIXES
        cout << "Six Soldiers will have power of 6" << endl;
        for (int i = 0; i < 6; i++) {
            cout << "Pick a location for 6* soldier number: " << (i + 1) << endl;


            cout << "Pick a X coordinate (left side is 0)" << endl;
            cin >> blockY;

            cout << "Pick a Y coordinate (6 to 8)" << endl;
            cin >> blockX;//block x and Y got switched somehow


            if (blockX >= 6 && blockY <= 8) {
                Gamepiece *p = new Gamepiece(6, 1, blockY, blockX, idcounter, "SOLDIER");

                if (game->addGamepiece(p)) {
                    idcounter++;
                    cout << "Your soldier has been placed" << endl;
                } else {
                    i--;
                    cout << "try again..." << endl;
                    cout << endl;
                }
            } else {
                cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
                i--;
            }
            game->printGrid();
        }
        //FIVE FIVES
        cout << "Five Soldiers will have power of 5" << endl;
        for (int i = 0; i < 5; i++) {
            cout << "Pick a location for 5* soldier number: " << (i + 1) << endl;


            cout << "Pick a X coordinate (left side is 0)" << endl;
            cin >> blockY;

            cout << "Pick a Y coordinate (6 to 8)" << endl;
            cin >> blockX;//block x and Y got switched somehow


            if (blockX >= 6 && blockY <= 8) {
                Gamepiece *p = new Gamepiece(5, 1, blockY, blockX, idcounter, "SOLDIER");

                if (game->addGamepiece(p)) {
                    idcounter++;
                    cout << "Your soldier has been placed" << endl;
                } else {
                    i--;
                    cout << "try again..." << endl;
                    cout << endl;
                }
            } else {
                cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
                i--;
            }
            game->printGrid();
        }


        //FOUR FOURS
        cout << "four Soldiers will have power of 4" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "Pick a location for 4* soldier number: " << (i + 1) << endl;


            cout << "Pick a X coordinate (left side is 0)" << endl;
            cin >> blockY;

            cout << "Pick a Y coordinate (6 to 8)" << endl;
            cin >> blockX;//block x and Y got switched somehow


            if (blockX >= 6 && blockY <= 8) {
                Gamepiece *p = new Gamepiece(4, 1, blockY, blockX, idcounter, "SOLDIER");

                if (game->addGamepiece(p)) {
                    idcounter++;
                    cout << "Your soldier has been placed" << endl;
                } else {
                    i--;
                    cout << "try again..." << endl;
                    cout << endl;
                }
            } else {
                cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
                i--;
            }
            game->printGrid();
        }

        //THREE THREES
        cout << "four Soldiers will have power of 3" << endl;
        for (int i = 0; i < 3; i++) {
            cout << "Pick a location for 3* soldier number: " << (i + 1) << endl;


            cout << "Pick a X coordinate (left side is 0)" << endl;
            cin >> blockY;

            cout << "Pick a Y coordinate (6 to 8)" << endl;
            cin >> blockX;//block x and Y got switched somehow


            if (blockX >= 6 && blockY <= 8) {
                Gamepiece *p = new Gamepiece(3, 1, blockY, blockX, idcounter, "SOLDIER");

                if (game->addGamepiece(p)) {
                    idcounter++;
                    cout << "Your soldier has been placed" << endl;
                } else {
                    i--;
                    cout << "try again..." << endl;
                    cout << endl;
                }
            } else {
                cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
                i--;
            }
            game->printGrid();
        }

        //TWO TWOS
        cout << "Two Soldiers will have power of 2" << endl;
        for (int i = 0; i < 2; i++) {
            cout << "Pick a location for 2* soldier number: " << (i + 1) << endl;


            cout << "Pick a X coordinate (left side is 0)" << endl;
            cin >> blockY;

            cout << "Pick a Y coordinate (6 to 8)" << endl;
            cin >> blockX;//block x and Y got switched somehow


            if (blockX >= 6 && blockY <= 8) {
                Gamepiece *p = new Gamepiece(2, 1, blockY, blockX, idcounter, "SOLDIER");

                if (game->addGamepiece(p)) {
                    idcounter++;
                    cout << "Your soldier has been placed" << endl;
                } else {
                    i--;
                    cout << "try again..." << endl;
                    cout << endl;
                }
            } else {
                cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
                i--;
            }
            game->printGrid();
        }

        //A SINGLE ONE
        cout << "You only get one soldier with power of 1" << endl;
        for (int i = 0; i < 1; i++) {
            cout << "Pick a location for 1* soldier number: " << (i + 1) << endl;


            cout << "Pick a X coordinate (left side is 0)" << endl;
            cin >> blockY;

            cout << "Pick a Y coordinate (6 to 8)" << endl;
            cin >> blockX;//block x and Y got switched somehow


            if (blockX >= 6 && blockY <= 8) {
                Gamepiece *p = new Gamepiece(1, 1, blockY, blockX, idcounter, "SOLDIER");

                if (game->addGamepiece(p)) {
                    idcounter++;
                    cout << "Your soldier has been placed" << endl;
                } else {
                    i--;
                    cout << "try again..." << endl;
                    cout << endl;
                }
            } else {
                cout << "You can only fill the bottom three rows. (6,7, and 8)" << endl;
                i--;
            }
            game->printGrid();
        }
    }

    //Automatic placement of player pieces
    for (int i = 0; i < 1; i++)// FLAG
    {
        Gamepiece *p = new Flag(1, 9, 9, idcounter);
        game->addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 6; i++)//power 6
    {
        blockX = i;
        Gamepiece *p = new Gamepiece(6, 1, 7 - i, 8, idcounter, "SOLDIER");
        game->addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 2; i++)// power 2
    {
        blockX = i;
        Gamepiece *p = new Gamepiece(2, 1, 1 - i, 8, idcounter, "SOLDIER");
        game->addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 5; i++)// BOMBS
    {
        blockX = i;
        Gamepiece *p = new Bomb(1, i, 7, idcounter);
        game->addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 4; i++)// power 4
    {
        blockX = i;
        Gamepiece *p = new Gamepiece(4, 1, i + 5, 7, idcounter, "SOLDIER");
        game->addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 3; i++)// power 3
    {
        blockX = i;
        Gamepiece *p = new Gamepiece(3, 1, i, 6, idcounter, "SOLDIER");
        game->addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 5; i++)// power 5
    {
        blockX = i;
        Gamepiece *p = new Gamepiece(5, 1, i, 9, idcounter, "SOLDIER");
        game->addGamepiece(p);
        idcounter++;
    }

    for (int i = 0; i < 1; i++)// power 1
    {
        blockX = i;
        Gamepiece *p = new Gamepiece(1, 1, 8, 6, idcounter, "SOLDIER");
        game->addGamepiece(p);
        idcounter++;
    }
	for (int i = 0; i < 1; i++)// TheS py
    {
        blockX = i;
        Gamepiece *p = new Gamepiece(10, 1, 9, 6, idcounter, "SPY");
        game->addGamepiece(p);
        idcounter++;
    }
	
	for (int i = 0; i < 5; i++)// Five Miners
    {
        blockX = i;
        Gamepiece *p = new Gamepiece(8, 1, i + 3, 6, idcounter, "MINER");
        game->addGamepiece(p);
        idcounter++;
    }
    //Automatic placement of player pieces Complete


    cout << endl;
    cout << "THE BOARD IS SET" << endl;
    cout << "THE GAME WILL NOW BEGIN!" << endl;
    cout << endl;
    game->printGrid();
    cout << endl;
    cout << endl;


    while (moreMove) {
        // this will be changed to an array
        vector<string> pvec = game->scancount(1);//could be used for more, but the other features are not helpfull
        cout << pname << " it is your turn." << endl;
        cout << "You have " << pvec.size() << " pieces under your command" << endl;

        cout << "Pick a X coordinate for a movable block:" << endl;
        cin >> moveY;

        cout << "Pick an Y Coordinate for a movable block:" << endl;
        cin >> moveX;

        if (game->findcell(moveY, moveX) == nullptr) {
            cout << "That space is empty" << endl;
            cout << "try again..." << endl;
        } else if ((game->findcell(moveY, moveX))->getteam() == 2) {
            cout << "That is not your piece" << endl;
            cout << "try again..." << endl;
        } else {
            cout << "Pick a direction 1:up, 2:down, 3:left, or 4:right?" << endl;
            cin >> direction;

            b = game->findcell(moveY, moveX);
            if (game->move(direction, b)) {
                game->printGrid();
                cout << endl;
				cout << "The Computer is now taking its turn" << endl << endl;

                game->takeComputerTurn();
				cout << endl << "The Computer has made its turn" << endl;
            }

        }

        game->printGrid();

        if (game->findwinner() != 0) {
            cout << "PLAYER " << game->findwinner() << " WINS!" << endl;
            moreMove = false;
        }

    }
    return 0;
}