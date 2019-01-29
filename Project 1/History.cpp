//history.cpp
//---------
//Adam Cole
//004912373
//Discusssion 1E
//---------

#include "History.h"
#include "globals.h"

#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
	totalcolumn = nCols;
	totalrow = nRows;
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			histo[i][j] = 0;
		}
	}
}

History::~History() {
	//write an expression to have histo be deleted
	int j = histo[totalrow - 1][totalcolumn - 1];
}

bool History::record(int r, int c) {
	if (r <= 0 || r > totalrow || c <= 0 || c > totalcolumn) {
		return false;
	}
	//"Record what it needs to"
	histo[r - 1][c - 1]++;
	return true;
}

void History::display() const {
	//clear the screen
	clearScreen();

	//display the history grid
	// Position (row,col) in the city coordinate system is represented in
	// the array element grid[row-1][col-1]
	char grid[MAXROWS][MAXCOLS];
	int r, c;

	// Fill the grid with dots
	for (r = 0; r < totalrow; r++)
		for (c = 0; c < totalcolumn; c++)
			grid[r][c] = '.';

	//	Add the corresponding values for each position
	for (int i = 0; i < totalrow; i++) {
		for (int j = 0; j < totalcolumn; j++) {
			if (histo[i][j] != 0) {
				//'@' is the character before 'A' in the ascii table
				grid[i][j] = '@' + histo[i][j];
			}
		}
	}
	// Draw the grid
	for (r = 0; r < totalrow; r++)
	{
		for (c = 0; c < totalcolumn; c++)
			cout << grid[r][c];
		cout << endl;
	}
	//write an empty line after the grid
	cout << endl;
}
