//maze.cpp
//
//Adam Cole
//004912373
//
//Homework 3
//Problem 3

//#include <iostream>
//using namespace std;

//Coord class
//class Coord {
//public:
//	Coord(int rr = 0, int cc = 0) : m_r(rr), m_c(cc) {}	//constructor
//	int r() const { return m_r; }	//return row
//	int c() const { return m_c; }	//return col
//private:
//	int m_r;		//row
//	int m_c;		//column
//};

//south = increasing r
//north = decreasing r
//east= increasing c
//west = decreasing c

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	//if start is equal to the end, solved!
	if (sr == er && sc == ec)
		return true;
	//mark the first spot discovered
	maze[sr][sc] = 'D';
	//check the four directions
	//------------------------
	//north
	if (maze[sr - 1][sc] == '.') {
		if (pathExists(maze, sr - 1, sc, er, ec))
			return true;
	}
	//south
	if (maze[sr + 1][sc] == '.') {
		if (pathExists(maze, sr + 1, sc, er, ec))
			return true;
	}
	//west
	if (maze[sr][sc - 1] == '.') {
		if (pathExists(maze, sr, sc - 1, er, ec))
			return true;
	}
	//east
	if (maze[sr][sc + 1] == '.') {
		if (pathExists(maze, sr, sc + 1, er, ec))
			return true;
	}
	return false;
}

//PSEUDOCODE:

//	If the start location is equal to the ending location, then we've
//		solved the maze, so return true.
//	Mark the start location as visted.
//	For each of the four directions,
//		If the location one step in that direction(from the start location) is unvisited,
//				then call pathExists starting from that location(and
//					ending at the same ending location as in the
//					current call).
//				If that returned true,
//					then return true.
//	Return false.

//int main
//int main() {
//	char maze[10][10] = {
//		{ 'X','X','X','X','X','X','X','X','X','X' },
//	{ 'X','.','.','.','.','.','.','.','.','X' },
//	{ 'X','X','X','X','X','.','X','.','X','X' },
//	{ 'X','.','.','.','X','.','X','.','.','X' },
//	{ 'X','.','X','.','.','.','X','.','.','X' },
//	{ 'X','.','X','X','X','.','X','X','X','X' },
//	{ 'X','X','X','.','.','.','.','X','.','X' },
//	{ 'X','.','X','X','.','X','X','X','.','X' },
//	{ 'X','.','.','.','.','X','.','.','.','X' },
//	{ 'X','X','X','X','X','X','X','X','X','X' }
//	};
//
//	if (pathExists(maze, 6, 5, 1, 8))
//		cout << "Solvable!" << endl;
//	else
//		cout << "Out of luck!" << endl;
//}