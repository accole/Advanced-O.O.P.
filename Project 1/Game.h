//game.h
//---------
//Adam Cole
//004912373
//Discusssion 1E
//---------

#ifndef GAME_H
#define GAME_H

class City;

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nFlatulans);
	~Game();

	// Mutators
	void play();

private:
	City * m_city;
};

#endif //GAME_H
