#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>


//------------------------------------------------------------------------------
//m_screen coordinates of headings

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

//------------------------------------------------------------------------------
//non-member functions declarations

bool validRecursion(Piece* s, int sx, int sy);
int maximum(int x, int y);

//------------------------------------------------------------------------------
//functions given to us in skeleton

Game::Game(int width, int height)
 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_score(0), m_rowsleft(5*m_level)
{
	//dynamically allocate the new char's
	/*for (int i = 0; i < height + 1; i++) {
		for (int j = 0; j < width + 2; j++) {
			m_placedPieces[i][j] = new char;
		}
	}*/
	//clear the well and initialize the values
	clearWell();
}

void Game::play()
{
	//10, 18 are the dimensions given in chetyris.cpp
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
	// [Replace this with code to display the status.]
	//
	//first character of the 7 spaces should be at x = 27 m_screen coordinates
	//27 + (7 - y) = xcoordinate of where the first number should be
	//34 - y
	//
	//Score
	m_screen.gotoXY(SCORE_X, SCORE_Y);
	m_screen.printString("Score:     ");
	std::string x = std::to_string(m_score);
	int y = x.length();
	m_screen.gotoXY(34 - y, 8);
	m_screen.printString(x);
	//Rows Left
	m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
	m_screen.printString("Rows left: ");
	x = std::to_string(m_rowsleft);
	y = x.length();
	m_screen.gotoXY(34 - y, 9);
	m_screen.printString(x);
	//Level
	m_screen.gotoXY(LEVEL_X, LEVEL_Y);
	m_screen.printString("Level:     ");
	x = std::to_string(m_level);
	y = x.length();
	m_screen.gotoXY(34 - y, 10);
	m_screen.printString(x);
}

bool Game::playOneLevel()
{
	//start each level with a clean well
	clearWell();

	//polymorphism
	Piece* next = nullptr;
	Piece* current = nullptr;

	//set a timer
	Timer timer;

	//assign current a random piece
	switch (chooseRandomPieceType()) {
	case PIECE_I:
		current = new Ipiece();
		break;
	case PIECE_L:
		current = new Lpiece();
		break;
	case PIECE_J:
		current = new Jpiece();
		break;
	case PIECE_O:
		current = new Opiece();
		break;
	case PIECE_S:
		current = new Spiece();
		break;
	case PIECE_Z:
		current = new Zpiece();
		break;
	case PIECE_T:
		current = new Tpiece();
		break;
	case PIECE_CRAZY:
		current = new CrazyShape();
		break;
	case PIECE_FOAM:
		current = new FoamBomb();
		break;
	case PIECE_VAPOR:
		current = new VaporBomb();
		break;
	case NUM_PIECE_TYPES:
		break;
	}

	//set the number of rows left in the level
	m_rowsleft = 5 * m_level;

	//play until 5*m_level rows have been eliminated
	while (m_rowsleft != 0) {

		//generate a new 'next' piece
		switch (chooseRandomPieceType()) {
		case PIECE_I:
			next = new Ipiece();
			break;
		case PIECE_L:
			next = new Lpiece();
			break;
		case PIECE_J:
			next = new Jpiece();
			break;
		case PIECE_O:
			next = new Opiece();
			break;
		case PIECE_S:
			next = new Spiece();
			break;
		case PIECE_Z:
			next = new Zpiece();
			break;
		case PIECE_T:
			next = new Tpiece();
			break;
		case PIECE_CRAZY:
			next = new CrazyShape();
			break;
		case PIECE_FOAM:
			next = new FoamBomb();
			break;
		case PIECE_VAPOR:
			next = new VaporBomb();
			break;
		case NUM_PIECE_TYPES:
			break;
		}

		//loop while a piece is falling
		while (!current->placed()) {

			//display the game
			displayGame(current, next);

			//test to see if the well is filled all the way up
			if (overlap(current)) {
				//delete all the newed pieces
				delete current;
				current = nullptr;
				delete next;
				next = nullptr;
				//return false
				return false;
			}

			//start the timer
			timer.start();

			//in between falling motions
			while (timer.elapsed() < maximum(1000 - (100 * (m_level - 1)), 100)) {
				char ch;
				//test for keystrokes by user
				if (getCharIfAny(ch)) {
					//character was typed
					switch (ch) {
					case 'q':
					case 'Q':
						//delete all the newed pieces
						delete current;
						current = nullptr;
						delete next;
						next = nullptr;
						//return false
						return false;
					case ARROW_LEFT:
						//Crazy Piece will go the opposite direction
						if (current->getType() == PIECE_CRAZY) {
							//test if next to the left well
							if (wallNextToPiece(current, 'R')) {}
							//dont move the piece
							else {
								//move the piece left
								current->moveLeft();
								//displayGame(current, next);
							}
						}
						else {
							//normal piece
							//test if next to the left well
							if (wallNextToPiece(current, 'L')) {}
							//dont move the piece
							else {
								//move the piece left
								current->moveLeft();
								//displayGame(current, next);
							}
						}
						break;
					case ARROW_RIGHT:
						//crazy piece will go the opposite direction
						if (current->getType() == PIECE_CRAZY) {
							//test if next to the left well
							if (wallNextToPiece(current, 'L')) {
								//dont move the piece
							}
							else {
								//move the piece right
								current->moveRight();
								//displayGame(current, next);
							}
						}
						else {
							//test if next to the right well
							if (wallNextToPiece(current, 'R')) {
								//dont move the piece
							}
							else {
								//move the piece right
								current->moveRight();
								//displayGame(current, next);
							}
						}
						break;
					case ARROW_UP: {
						//check is the next orientation is valid
						current->rotate();
						if (overlap(current)) {
							//move all the way back to original orientation
							current->rotate();
							current->rotate();
							current->rotate();
						}
						//else let it rotate
						//displayGame(current, next);
						}
						break;
					case ARROW_DOWN:
						//test if reached the bottom of the well
						if (wallBelowPiece(current)) {
							//add the piece to m_placedPieces
							current->setplace(true);
							if (specialAction(current)) {
								//do nothing else
							}
							else {
								addPiece(current);
							}
						}
						else {
							//move the piece down
							current->moveDown();
							//displayGame(current, next);
						}
						break;
					case ' ':
						//move the piece all the way down the well
						while (!wallBelowPiece(current)) {
							current->moveDown();
						}
						current->setplace(true);
						if (specialAction(current)) {
							//do nothing else
						}
						else {
							addPiece(current);
						}
						break;
					default:
						//nothing
						break;
					}
					//if the user pressed any keys
					displayGame(current, next);
				}

			}
			//after time
			//-------------
			//test if piece has already been placed first
			if (!current->placed()) {

				//test if reached the bottom of the well
				if (wallBelowPiece(current)) {
					//add the piece to m_placedPieces
					current->setplace(true);
					if (specialAction(current)) {
						//do nothing else
					}
					else {
						addPiece(current);
					}
				}
				else {
					//time has passed and piece must move down
					current->moveDown();
				}
			}
		}
		//delete the "newed" current piece
		Piece* temp = current;
		delete temp;
		temp = nullptr;
		current = next;

		//check for rows to vaporize if any
		if (numFull() != 0) {
			//update the score and decrement rowsleft
			if (numFull() < 3) {
				//normal amount of points per row
				m_score += (numFull() * 100);
			}
			else {
				//special amounts of points
				//exponential
				int money = 1;
				for (int i = 0; i < numFull() - 2; i++) {
					money *= 2;
				}
				m_score += (200 * money);
			}
			m_rowsleft -= numFull();
			//if level is now over, don't clear the rows
			if (m_rowsleft <= 0) { m_rowsleft = 0; }
			else { clearRows(); }
		}
	}

	//display one last time before the message
	displayGame(next);

	//delete all the newed pieces
	delete current;
	current = nullptr;
	next = nullptr;

	//if they vaporize 5 rows*m_level, return true
	return true;
}

//-------------------------------------------------------------------------------
//my added functions

						//destructor

Game::~Game() {
	//delete all the dynamically allocated memory made during construction
	//for (int i = 0; i < 19; i++) {
	//	for (int j = 0; j < 12; j++) {
	//		//free the memory
	//		delete m_placedPieces[i][j];
	//		//point the address to the nullptr
	//		m_placedPieces[i][j] = nullptr;
	//	}
	//}
}

						//displaying pieces falling

void Game::displayPiece(Piece* s) {
	//getX() and getY() are the starting coordinates for the (0,0)
	//	element of the 4x4 bounding box
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (s->getbox(i, j) == '#') {
				//4x4 bounding box --> gotoXY()
				m_screen.gotoXY(s->getX() + j, s->getY() + i);
				m_screen.printChar('#');
			}
		}
	}
}

void Game::displayPiece(Piece* s, int x, int y) {
	//x and y are the starting coordinates for the (0,0)
	//	element of the 4x4 bounding box
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (s->getbox(i, j) == '#') {
				//4x4 bounding box --> gotoXY()
				m_screen.gotoXY(x + j, y + i);
				m_screen.printChar('#');
			}
		}
	}
}


						//modifying the well and placed pieces

void Game::addPiece(Piece* s) {
	//adds the placed piece to m_placedPieces
	//
	//bounding box 'array' coordinates
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//Bounding Box --> m_placed pieces
			char c = s->getbox(i, j);
			if (c != ' ') {
				/* * */(m_placedPieces[s->getY() + i][s->getX() + j]) = '$';
			}
		}
	}
}

void Game::clearWell() {
	//adds left and right well walls to placedPieces
	for (int i = 0; i < 19; i++) {
		/* * */(m_placedPieces[i][0]) = '@';
		/* * */(m_placedPieces[i][11]) = '@';
	}
	//adds the bottom well wall to placedPieces
	for (int j = 1; j < 11; j++) {
		/* * */(m_placedPieces[18][j]) = '@';
	}
	//initializes the middle of the well in placedPieces to empty
	for (int i = 0; i < 18; i++) {
		for (int j = 1; j < 11; j++) {
			/* * */(m_placedPieces[i][j]) = ' ';
		}
	}
}

						//special pieces

bool Game::specialAction(Piece* s) {
	//PRECONDITION: piece s is placed and ready to do the special action
	//POSTCONDITION: if the piece has a special action, m_placedPieces will be 
	//				 modified and it will return true, else return false
	PieceType x = s->getType();
	if (x == PIECE_VAPOR) {
		//must ensure vaporbomb doesn't try to access elements outside of the well!
		int xposition = s->getX() + 1;
		int yposition = s->getY();
		if (yposition - 2 < 0) {
			//vaporbomb at the top of the well
			//start from the top of the well -> go to the bottom of vaporbomb
			for (int i = 0; i < yposition + 3; i++) {
				/* * */(m_placedPieces[i][xposition]) = ' ';
				/* * */(m_placedPieces[i][xposition + 1]) = ' ';
			}
		}
		else if (yposition + 2 > 17) {
			//vaporbomb is at the bottom of the well
			//start from the top of vaporbomb -> go to the bottom of well
			for (int i = yposition - 2; i < 18; i++) {
				/* * */(m_placedPieces[i][xposition]) = ' ';
				/* * */(m_placedPieces[i][xposition + 1]) = ' ';
			}
		}
		else {
			//middle of the well
			//vaporize 2 above and 2 below the vaporbomb
			for (int i = yposition - 2; i < yposition + 3; i++) {
				/* * */(m_placedPieces[i][xposition]) = ' ';
				/* * */(m_placedPieces[i][xposition + 1]) = ' ';
			}
		}
		return true;
	}
	else if (x == PIECE_FOAM) {
		//coordinates for where the '#' is in foambomb for orientation 0
		recursiveFoam(s, s->getX() + 1, s->getY() + 1);
		return true;
	}
	else {
		//no special action, do nothing
		return false;
	}
}

bool Game::recursiveFoam(Piece * s, int sx, int sy) {
	//PRECONDITION: only valid coordinates are passed into the recursive function
	//				'sx' and 'sy' are m_screen coordinates
	//POSTCONDITION: returns true if the next piece is accessible and valid
	//				false if no valid next move
	
	//mark the current position as 'accessible'
	/* * */(m_placedPieces[sy][sx]) = '*';
	//check the four directions
	//------------------------
	//Up
	if (validRecursion(s, sx, sy - 1)) {
		//then next coordinate is valid
		//if the valid space is empty
		if (/* * */(m_placedPieces[sy - 1][sx]) == ' ') {
			//recursively call to that position
			recursiveFoam(s, sx, sy - 1);
		}
	}
	//down
	if (validRecursion(s, sx, sy + 1)) {
		//then next coordinate is valid
		//if the valid space is empty
		if (/* * */(m_placedPieces[sy + 1][sx]) == ' ') {
			//recursively call
			recursiveFoam(s, sx, sy + 1);
		}
	}
	//left
	if (validRecursion(s, sx - 1, sy)) {
		//then next coordinate is valid
		//if the valid space is empty
		if (/* * */(m_placedPieces[sy][sx - 1]) == ' ') {
			//recursively call
			recursiveFoam(s, sx - 1, sy);
		}
	}
	//right
	if (validRecursion(s, sx + 1, sy)) {
		//then next coordinate is valid
		//if the valid space is empty
		if (/* * */(m_placedPieces[sy][sx + 1]) == ' ') {
			//recursively call
			recursiveFoam(s, sx + 1, sy);
		}
	}
	//base case	- current coordinate can't move anywhere validly
	return false;
}

bool validRecursion(Piece* s, int sx, int sy) {
	//PRECOND: 'sx' and 'sy' are m_screen coordinates of where the next coord is
	//POSTCOND: will return true if the current coordinate does not go outside of
	//			the well or the 5x5 bomb box
	//tests if x coordinate or y coordinate exceed well's boundary
	bool well = (sx < 11 && sx > 0) && (sy < 18 && sy > -1);
	//tests if x coord or y coord exceeds foambomb's 5x5 bomb box
	bool box = (sx < (s->getX()+1) + 3 && sx > (s->getX()+1) - 3) && (sy > (s->getY()+1) - 3 && sy < (s->getY()+1) + 3);
	return well && box;
}

						//clearing rows
int Game::numFull() {
	//create an int to increment the number of rows cleared
	int cleared = 0;
	//loop from bottom of the well to top
	for (int i = 17; i > -1; i--) {
		//test if the row needs to be cleared
		if (fullRow(i)) {
			//increment the number of cleared rows
			cleared++;
		}
		//else move to next row
	}
	return cleared;
}

void Game::clearRows() {
	//loop from bottom of the well to top
	for (int i = 17; i > 0; i--) {
		//test if the row needs to be cleared
		if (fullRow(i)) {
			//clear the row
			//-------------
			//for()loop up the rows from the one that needs to be cleared
			//	but not the top row!
			for (int k = i; k > 0; k--) {
				//for()loop along the row -> and
				for (int j = 1; j < 11; j++) {
					//copy the *value of the elements above each into bottom element
					/* * */(m_placedPieces[k][j]) = /* * */(m_placedPieces[k - 1][j]);
				}
			}
			//set the top row to blank spaces
			for (int j = 1; j < 11; j++) {
				/* * */(m_placedPieces[0][j]) = ' ';
			}
			//move the first for loop's 'i' back one
			//since we moved all the rows down
			i++;
		}
		//else move to the next row
	}
	return;
}

bool Game::fullRow(int row) {
	//returns true if the row of m_placedPieces is full and 
	//	ready to be cleared
	//returns false otherwise
	for (int i = 1; i < 11; i++) {
		//if any value in the row is a space, not full
		if (/* * */(m_placedPieces[row][i]) == ' ')
			return false;
	}
	//if all the elements don't return false, return true
	return true;
}

						//testing boundaries of the well

bool Game::wallBelowPiece(Piece* s) {
	//loop through the 4x4 bounding box of the piece
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//'array' coordinates not m_screen
			char c = s->getbox(i, j);
			//where there's a character in the 4x4 bounding box
			if (c != ' ') {
				//if there's a character below it **([_ + 1][_]) in m_placedPieces
				//i and j = 'array coordinates' of boundingbox piece coordinates
				//getY() and getX() = 'm_screen coordinates' of pieces' position
				char b = /* * */(m_placedPieces[s->getY() + i + 1][s->getX() + j]);
				if (b != ' ') {
					//then theres a wall or a boundary below the shape
					return true;
				}
			}
		}
	}
	//if it loops through the whole shape and nothing is below it, no wall beneath
	return false;
}

bool Game::wallNextToPiece(Piece* s, char a) {
	//loop through the 4x4 bounding box of the piece
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//'array' coordinates not m_screen
			char c = s->getbox(i, j);
			//where there's a character in the 4x4 bounding box
			if (c != ' ') {
				//if there's a character next to it **([_][_ + or - 1]) in m_placedPieces
				//i = 'array coordinates' of boundingbox piece coordinates
				//getY() and getX() = 'm_screen coordinates' of pieces' position
				char b;
				if (a == 'R') {
					//test to the right
					b = /* * */(m_placedPieces[s->getY() + i][s->getX() + j + 1]);
				}
				else {
					//test to the left
					b = /* * */(m_placedPieces[s->getY() + i][s->getX() + j - 1]);
				}
				if (b != ' ') {
					//then theres a wall or a boundary below the shape
					return true;
				}
			}
		}
	}
	//if it loops through the whole shape and nothing is below it, no wall beneath
	return false;
}

bool Game::overlap(Piece* s) {
	//loop through the 4x4 bounding box of the piece
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//'array' coordinates not m_screen
			char c = s->getbox(i, j);
			//where there's a character in the 4x4 bounding box
			if (c != ' ') {
				//if there's a character at the same spot in m_placedPieces
				//i = 'array coordinates' of boundingbox piece coordinates
				//getY() and getX() = 'm_screen coordinates' of pieces' position
				char b = /* * */(m_placedPieces[s->getY() + i][s->getX() + j]);
				if (b != ' ') {
					//then the piece overlaps another one
					return true;
				}
			}
		}
	}
	//if it loops through the whole shape and nothing is below it, no wall beneath
	return false;
}

						//displaying placed pieces

void Game::displayPlacedPieces() {
	//only want to output the 'inside' of the well - not the walls too
	//'array' coordinates
	for (int i = 17; i > -1; i--) {
		for (int j = 10; j > 0; j--) {
			char c = /* * */(m_placedPieces[i][j]);
			if (c != ' ') {
				//then there's a character we need to display
				//'m_screen coordinates'
				m_screen.gotoXY(j, i);
				m_screen.printChar(c);
			}
		}
	}
}

						//displaying the entire game screen

void Game::displayGame(Piece* current, Piece* next) {
	//clear the screen
	m_screen.clear();
	//display the well
	m_well.display(m_screen, WELL_X, WELL_Y);
	//display the score, level, rowsleft
	displayStatus();
	//display the prompt
	if (m_level == 1)
		displayPrompt("Press the Enter key to begin playing Chetyris!");
	else
		displayPrompt("Good job!  Press the Enter key to start next level!");
	//display next piece title
	m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
	m_screen.printString("Next piece:");
	//display the next piece
	displayPiece(next, NEXT_PIECE_X, NEXT_PIECE_Y);
	//display the placed pieces at bottom of well
	displayPlacedPieces();
	//display the current piece falling
	displayPiece(current);
}

void Game::displayGame(Piece* next) {
	//clear the screen
	m_screen.clear();
	//display the well
	m_well.display(m_screen, WELL_X, WELL_Y);
	//display the score, level, rowsleft
	displayStatus();
	//display the prompt
	if (m_level == 1)
		displayPrompt("Press the Enter key to begin playing Chetyris!");
	else
		displayPrompt("Good job!  Press the Enter key to start next level!");
	//display next piece title
	m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
	m_screen.printString("Next piece:");
	//display the next piece
	displayPiece(next, NEXT_PIECE_X, NEXT_PIECE_Y);
	//display the placed pieces at bottom of well
	displayPlacedPieces();
}

						//extra functions

int maximum(int x, int y) {
	if (x > y)
		return x;
	else
		return y;
}

//-------------------------------------------------------------------------------
//notes:

							//index clarification

//Bounding Box
//	[0-4][0-4]
//	[rows(y)][cols(x)]

//m_placedPieces
//	[0-17][1-10]			*inside well
//	[0-18][0-11]		*including walls
//	[rows(y)][cols(x)]
												//**notice the only difference
//m_screen well										between m_placedPieces and
//	(0-11, 0-18)									m_screen coordinates are the
//	(columns(x), rows(y))							order