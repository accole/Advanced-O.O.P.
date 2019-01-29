//history.h
//---------
//Adam Cole
//004912373
//Discusssion 1E
//---------

#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"

class History {
public:
	History(int nRows, int nCols);
	~History();
	bool record(int r, int c);
	void display() const;
private:
	int totalrow;
	int totalcolumn;
	int histo[MAXROWS][MAXCOLS];
};

#endif //HISTORY_H
