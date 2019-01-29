#include "Piece.h"
#include "Well.h"

//----------------------------------
//Piece SuperClass implementations

						//constructors
Piece::Piece() {
	//base coordinates are at X=3, Y=0
	xpos = 4;
	ypos = 0;
	//originally not placed
	place = false;
	//originally no piece type
	x = NUM_PIECE_TYPES;
	//create the 4 orientation linked list
	Node* orientation0 = new Node;
	Node* orientation1 = new Node;
	Node* orientation2 = new Node;
	Node* orientation3 = new Node;
	//fix all the arrows
	m_head = orientation0;
	orientation0->next = orientation1;
	orientation1->next = orientation2;
	orientation2->next = orientation3;
	orientation3->next = orientation0;
	//inialize all the orientations to empty;
	Node* temp = orientation0;
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				temp->o[i][j] = ' ';
			}
		}
		temp = temp->next;
	}
	//update boundingbox to orientation 0
	orientation2boundingbox();
	m_orientation = 0;
}
Piece::Piece(const Piece& other) {
	//copy over regular data
	xpos = other.xpos;
	ypos = other.ypos;
	place = other.place;
	//copy over the piecetype
	x = other.x;
	//create the 4 orientation linked list Nodes
	Node* o0 = new Node;
	Node* o1 = new Node;
	Node* o2 = new Node;
	Node* o3 = new Node;
	//fix the arrows
	m_head = o0;
	o0->next = o1;
	o1->next = o2;
	o2->next = o3;
	o3->next = o0;
	//copy over the orientations
	Node* othertemp = other.m_head;
	Node* temp = m_head;
	for(int k = 0; k < 4; k++) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				temp->o[i][j] = othertemp->o[i][j];
			}
		}
		temp = temp->next;
		othertemp = othertemp->next;
	}
	//updatebounding box
	orientation2boundingbox();
	m_orientation = other.m_orientation;
}

						//dealing with m_screen
int Piece::getX() const { return xpos; }
int Piece::getY() const { return ypos; }
						//movement in game.cpp
void Piece::incrementX() { xpos++; }
void Piece::decrementX() { xpos--; }
void Piece::moveDown() { ypos++; }
void Piece::rotate() { next(); orientation2boundingbox(); }
						//acessing data
bool Piece::placed() const { return place; }
char Piece::getbox(int x, int y) const { return boundingbox[x][y]; }
PieceType Piece::getType() const { return x; }
int Piece::getOrientation() const { return m_orientation; }
						//changing data
void Piece::setplace(bool placed) { place = placed; }
void Piece::setType(PieceType s) { x = s; }
						//non-pure virtual
Piece::~Piece() {
	//delete all the allocated 'new' nodes made during construction
	Node* temp = m_head;
	m_head = nullptr;
	for (int k = 0; k < 4; k++) {
		if (k != 3) {
			Node * n = temp->next;
			delete temp;
			temp = n;
		}
		else {
			delete temp;
		}
	}
}
void Piece::moveRight() { incrementX(); }
void Piece::moveLeft() { decrementX(); }
						//pure-virtual
//nothing
						//protected
void Piece::addChar(int row, int col, char a) {
	//adds a character to the respective element in m_head's o
	m_head->o[row][col] = a;
}
void Piece::orientation2boundingbox() {
	//updates the bounding box to the correct orientation pointed
	//to by m_head
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			boundingbox[i][j] = m_head->o[i][j];
		}
	}
}
void Piece::next() { m_head = m_head->next; m_orientation++; }

//---------------------------------
//Piece Subclass Implementations
		//default constructors initialize the pieces to Orientation 0
		//and all the other orientations to each pieces' linked list

//NormalPiece Implementations

Ipiece::Ipiece() {
	//set the correct piecetype
	setType(PIECE_I);
	//fill in the orientations
	//orientation0 already pointed to
	for (int i = 0; i < 4; i++) {
		addChar(1, i, '#');
	}
	//move to the next orientation
	next();
	//fill in orientation1
	for (int i = 0; i < 4; i++) {
		addChar(i, 1, '#');
	}
	//move to the next orientation
	next();
	//fill in orientation2
	for (int i = 0; i < 4; i++) {
		addChar(1, i, '#');
	}
	//move to the next orientation
	next();
	//fill in orientation3
	for (int i = 0; i < 4; i++) {
		addChar(i, 1, '#');
	}
	//move m_head back to orientation0
	next();
	//fill the bounding box with the first orientation
	orientation2boundingbox();
}
Ipiece::~Ipiece() {/* nothing */ }
Opiece::Opiece() {
	//set the correct piecetype
	setType(PIECE_O);
	//orientation 0 for O piece is the same for all orientations
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				addChar(i, j, '#');
			}
		}
		next();
	}
	//fill the bounding box with the first orientation
	orientation2boundingbox();
}
Opiece::~Opiece() {/* nothing */ }
Jpiece::Jpiece() {
	//set the correct piecetype
	setType(PIECE_J);
	//orientation 0 for the J piece
	for (int i = 1; i < 4; i++) {
		addChar(1, i, '#');
	}
	addChar(2, 3, '#');
	//move m_head
	next();
	//orientation 1 for the J piece
	for (int i = 1; i < 4; i++) {
		addChar(i, 2, '#');
	}
	addChar(3, 1, '#');
	//move m_head
	next();
	//orientation 2 for the J piece
	for (int i = 1; i < 4; i++) {
		addChar(2, i, '#');
	}
	addChar(1, 1, '#');
	//move
	next();
	//orientation 3
	for (int i = 0; i < 3; i++) {
		addChar(i, 1, '#');
	}
	addChar(0, 2, '#');
	//move back to orientation 0
	next();
	//fill the bounding box with the first orientation
	orientation2boundingbox();
}
Jpiece::~Jpiece() {/* nothing */ }
Tpiece::Tpiece() {
	//set the correct piecetype
	setType(PIECE_T);
	//orientation 0 for the I piece
	for (int i = 0; i < 3; i++) {
		addChar(1, i, '#');
	}
	addChar(0, 1, '#');
	//move
	next();
	//orientation1
	for (int i = 0; i < 3; i++) {
		addChar(i, 1, '#');
	}
	addChar(1, 2, '#');
	//move
	next();
	//orientation2
	for (int i = 0; i < 3; i++) {
		addChar(1, i,'#');
	}
	addChar(2, 1, '#');
	//move
	next();
	//orientation 3
	for (int i = 0; i < 3; i++) {
		addChar(i, 1, '#');
	}
	addChar(1, 0, '#');
	//move back to orientation 0
	next();
	//fill the bounding box with the first orientation
	orientation2boundingbox();
}
Tpiece::~Tpiece() {/* nothing */ }
Lpiece::Lpiece() {
	//set the correct piecetype
	setType(PIECE_L);
	//orientation 0
	for (int i = 0; i < 3; i++) {
		addChar(1, i, '#');
	}
	addChar(2, 0,'#');
	//move
	next();
	//orientation 1
	for (int i = 0; i < 3; i++) {
		addChar(i, 2, '#');
	}
	addChar(0, 1, '#');
	//move
	next();
	//orientation 2
	for (int i = 0; i < 3; i++) {
		addChar(2, i, '#');
	}
	addChar(1, 2, '#');
	//move
	next();
	//orientation 3
	for (int i = 1; i < 4; i++) {
		addChar(i, 1, '#');
	}
	addChar(3, 2, '#');
	//move back to orientation 0
	next();
	//fill the bounding box with the first orientation
	orientation2boundingbox();
}
Lpiece::~Lpiece() {/* nothing */ }
Spiece::Spiece() {
	//set the correct piecetype
	setType(PIECE_S);
	//orientation 0
	for (int i = 0; i < 2; i++) {
		addChar(2, i, '#');
	}
	for (int i = 1; i < 3; i++) {
		addChar(1, i, '#');
	}
	//move
	next();
	//orientation 1
	for (int i = 0; i < 2; i++) {
		addChar(i, 1, '#');
	}
	for (int i = 1; i < 3; i++) {
		addChar(i, 2, '#');
	}
	//move
	next();
	//orientation 2
	for (int i = 0; i < 2; i++) {
		addChar(2, i, '#');
	}
	for (int i = 1; i < 3; i++) {
		addChar(1, i, '#');
	}
	//move
	next();
	//orientation 3
	for (int i = 0; i < 2; i++) {
		addChar(i, 1, '#');
	}
	for (int i = 1; i < 3; i++) {
		addChar(i, 2, '#');
	}
	//move
	next();
	//fill the bounding box with the first orientation
	orientation2boundingbox();
}
Spiece::~Spiece() {/* nothing */ }
Zpiece::Zpiece() {
	//set the correct piecetype
	setType(PIECE_Z);
	//orientation 0
	for (int i = 0; i < 2; i++) {
		addChar(1, i, '#');
	}
	for (int i = 1; i < 3; i++) {
		addChar(2, i, '#');
	}
	//move
	next();
	//orientation 1
	for (int i = 0; i < 2; i++) {
		addChar(i, 2, '#');
	}
	for (int i = 1; i < 3; i++) {
		addChar(i, 1, '#');
	}
	//move
	next();
	//orientation 2
	for (int i = 0; i < 2; i++) {
		addChar(1, i, '#');
	}
	for (int i = 1; i < 3; i++) {
		addChar(2, i, '#');
	}
	//move
	next();
	//orientation 3
	for (int i = 0; i < 2; i++) {
		addChar(i, 2, '#');
	}
	for (int i = 1; i < 3; i++) {
		addChar(i, 1, '#');
	}
	//move
	next();
	//fill the bounding box with the first orientation
	orientation2boundingbox();
}
Zpiece::~Zpiece() {/* nothing */ }

//SpecialPiece Implementations

VaporBomb::VaporBomb() {
	//set the correct piecetype
	setType(PIECE_VAPOR);
	for (int k = 0; k < 4; k++) {
		for (int i = 1; i < 3; i++) {
			addChar(0, i, '#');
		}
		next();
	}
	//fill the bounding box with the first orientation
	orientation2boundingbox();
}
VaporBomb::~VaporBomb() {/* nothing */ }

FoamBomb::FoamBomb() {
	//set the correct piecetype
	setType(PIECE_FOAM);
	for (int k = 0; k < 4; k++) {
		addChar(1, 1, '#');
		next();
	}
	//fill the bounding box with the first orientation
	orientation2boundingbox();
}
FoamBomb::~FoamBomb() {/* nothing */ }

CrazyShape::CrazyShape() {
	//set the correct piecetype
	setType(PIECE_CRAZY);
	//orientation 0
	addChar(0, 0, '#');
	addChar(0, 3, '#');
	addChar(1, 1, '#');
	addChar(1, 2, '#');
	//move
	next();
	//orientation 1
	addChar(3, 3, '#');
	addChar(0, 3, '#');
	addChar(2, 2, '#');
	addChar(1, 2, '#');
	//move
	next();
	//orientation 2
	addChar(3, 3, '#');
	addChar(2, 1, '#');
	addChar(2, 2, '#');
	addChar(3, 0, '#');
	//move
	next();
	//orientation 3
	addChar(0, 0, '#');
	addChar(2, 1, '#');
	addChar(1, 1, '#');
	addChar(3, 0, '#');
	//move back to orientation 0
	next();
	//fill the bounding box with the first orientation
	orientation2boundingbox();
}
CrazyShape::~CrazyShape() {/* nothing */ }
//crazy shape has backwards movement
void CrazyShape::moveRight() { decrementX(); }
void CrazyShape::moveLeft() { incrementX(); }