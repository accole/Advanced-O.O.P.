#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

//----------------------------------
//Piece SuperClass

class Piece {
public:
	Piece();
	Piece(const Piece& other);
	int getX() const;
	int getY() const;
	void incrementX();
	void decrementX();
	void rotate();
	void moveDown();
	bool placed() const;
	void setplace(bool placed);
	void setType(PieceType s);
	PieceType getType() const;
	char getbox(int row, int col) const;
	int getOrientation() const;
	//non-pure virtual functions
	virtual ~Piece();
	virtual void moveRight();
	virtual void moveLeft();
	//pure-virtual functions
protected:
	void addChar(int row, int col, char a);
	void orientation2boundingbox();
	void next();
private:
	struct Node {		//linked list to hold all 4 orientations of a piece
		char o[4][4];
		Node*next;
	};
	Node* m_head;	//head node to the list of orientations
	char boundingbox[4][4];	//current orientation
	int xpos;	//x coordinate of boundingbox[0][0] on m_screen
	int ypos;	//y coordinate of boundingbox[0][0] on m_screen
	bool place;	//boolean whether piece is placed or not
	PieceType x;//type of piece
	int m_orientation;	//which orientation the piece is currently in
};

//---------------------------------
//SubClasses of Piece

//Normal Pieces
//T, L, J, O, S, Z, I

class Ipiece : public Piece {
public:
	Ipiece();
	virtual ~Ipiece();
};

class Opiece : public Piece {
public:
	Opiece();
	virtual ~Opiece();
};

class Jpiece : public Piece {
public:
	Jpiece();
	virtual ~Jpiece();
};

class Tpiece : public Piece {
public:
	Tpiece();
	virtual ~Tpiece();
};

class Lpiece : public Piece {
public:
	Lpiece();
	virtual ~Lpiece();
};

class Spiece : public Piece {
public:
	Spiece();
	virtual ~Spiece();
};

class Zpiece : public Piece {
public:
	Zpiece();
	virtual ~Zpiece();
};

//Special Pieces
//Vapor, Foam, Crazy

class VaporBomb : public Piece {
public:
	VaporBomb();
	virtual ~VaporBomb();
};

class FoamBomb : public Piece {
public:
	FoamBomb();
	virtual ~FoamBomb();
};

class CrazyShape : public Piece {
public:
	CrazyShape();
	virtual ~CrazyShape();
	virtual void moveRight();
	virtual void moveLeft();
};

//---------------------------------
PieceType chooseRandomPieceType();

#endif // PIECE_INCLUDED