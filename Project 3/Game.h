#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    // [Add other members as necessary.]
	~Game();
	//-------------------------------------
	void displayPiece(Piece* p);
	void displayPiece(Piece* p, int x, int y);
	//-------------------------------------
	void addPiece(Piece* s);
	void clearWell();
	//-------------------------------------
	bool specialAction(Piece* s);
	bool recursiveFoam(Piece * s, int sx, int sy);
	//-------------------------------------
	int numFull();
	void clearRows();
	bool fullRow(int row);
	//-------------------------------------
	bool wallBelowPiece(Piece* s);
	bool wallNextToPiece(Piece* s, char a);
	bool overlap(Piece* s);
	//-------------------------------------
	void displayPlacedPieces();
	//-------------------------------------
	void displayGame(Piece* current, Piece* next);
	void displayGame(Piece* next);
  private:
    Well    m_well;
    Screen  m_screen;
    int     m_level;
    // [Add other members as necessary.]
	int		m_score;
	int		m_rowsleft;
	char	m_placedPieces[19][12];
};

#endif // GAME_INCLUDED
